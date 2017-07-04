#pragma once

#include <strategies/impl/greedyPG/greedyPGStrategy.h>

#include "parallelShardGPPG.h"

#include <omp.h>

#define SORT_BEFORE_PARALLEL 1

/**
 * This stategy employs the Greedy and Penalized Graph strategy in a parallel fashion.
 */
class GreedyParallelPGStrategy : public GreedyPenalizedGraphStrategy {

public:

  /**
   * Method to create this strategy with a said penality function.
   */
  GreedyParallelPGStrategy(const PGAlgorithm::PenalityFunction &penalityFunction, const unsigned int aParallelFactor) : GreedyPenalizedGraphStrategy(penalityFunction), parallelFactor(aParallelFactor) {
    allocatedShards = false;
  }

  /**
   * Destructor that will clean the shards data if the strategy was used.
   */
  virtual ~GreedyParallelPGStrategy() {
    freeShardsMemory();
  }

  /**
   * The parallel factor of the strategy.
   * @details This variable determines the size of the shards in terms of tasks. The final size of the shards will be parallelFactor times the # of PEs in the input. This is done like so to avoid unbalancing the PEs while they are calculated in shards.
   */
  const unsigned int parallelFactor; 

  /**
   * This method is automatically called before an invocation of the mapTasks method or when the strategy object is deconstructed.
   * @details This method can be called earlier to free the memory used. Only call this method after applying the strategy's output.
   */
  void freeShardsMemory() {
    if(allocatedShards) {
      delete []shards;
     allocatedShards = false;
    }
  }

protected:

  /**
   * A helper structure designed to serve as a comparator between two pointer to tasks.
   */
  #if SORT_BEFORE_PARALLEL
  
  struct TaskPointerComparator {
    bool operator()(Task *a, Task *b) const {
      return *(a) < *(b);
    }
  };

  #endif

  typedef ParallelShardGPPG<MinimalParallelInput, GreedyPenalizedGraphStrategy::MinHeap, GreedyPenalizedGraphStrategy::MaxHeap> Shard;

  /**
   * An array of shards, each containing a part of the original input in a local view.
   */
  Shard *shards;

  /**
   * This variable is a flag for the class, indicating that memory has been allocated and must be destroyed before the next strategy invocation.
   */
  bool allocatedShards;

  /**
   * The parallel computation over the shard of information.
   * @param shardId The shard position in the array.
   * @param refPEs A reference to the array of PEs in the input.
   * @param refTasks A reference to the array of tasks in the input.
   * @param PECount The number of PEs in the input.
   * @param shardSize The size, in tasks, every shard in the array but the unbalanced shard has.
   * @param thisShardSize The size, in tasks, of this shard. It defaults to the shardSize.
   */
  void computeShard(const unsigned int &shardId, BasePE *refPEs, Task *refTasks, const unsigned int &PECount, const unsigned int &shardSize, const unsigned int &thisShardSize) {
    MinimalParallelInput fragmentedInput(refPEs, &(refTasks[shardId*shardSize]), PECount, thisShardSize);
    auto shard = &shards[shardId];

    shard->setPECount(PECount);

    MaxHeap *tasksHeap = &(shard->tasksHeap);
    MinHeap *PEHeap = &(shard->PEHeap);
      
    populatePEHeap(fragmentedInput, PEHeap);
    populateTaskHeap(fragmentedInput, tasksHeap);

    executeGreedyStrategy(tasksHeap, PEHeap);
    shard->populateOutput(refTasks);
  }

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Strategy's input.
   */
  virtual void doTaskMapping(const MinimalParallelInput &input) {
    //############### Sanity Check ############################
    if(input.taskCount() == 0 || input.PECount() == 0) {
      return;
    }
    //#########################################################

    //############### Global execution variables ##############
    const unsigned int PECount = input.PECount();
    const unsigned int shardSize = PECount * parallelFactor;
    const unsigned int unbalancedShardSize = input.taskCount()%shardSize;
    const bool hasUnbalancedShard = unbalancedShardSize > 0;
    const unsigned int shardCount = input.taskCount() / shardSize + (hasUnbalancedShard); // false = 0; true = 1;
    
    assert(shardSize <= input.taskCount()); // The shard size cannot be greater than the whole input.
    //#########################################################

    //############### Previous Run memory cleanup #############
    freeShardsMemory();
    shards = new Shard[shardCount];
    allocatedShards = true;
    //#########################################################

    //############### Sorting The Task Array ##################
    Task *inputTasks = input.getTasks();
    
    #if SORT_BEFORE_PARALLEL

    std::vector<Task*> sortedTasks;
    for(unsigned int i = 0; i < input.taskCount(); ++i) {
      sortedTasks.push_back(inputTasks+i); 
    }
    std::make_heap(sortedTasks.begin(), sortedTasks.begin(), TaskPointerComparator());
    inputTasks = sortedTasks.front();

    #endif
    //#########################################################

    //############### Calculate Shards Step ###################
    #pragma omp parallel
    {

      // This OMP clausule treats the special case where there is one unbalanced shard with less elements than the others. It is issued before with the nowait keyword to alleviate the unbalance.
      #pragma omp single nowait
      {
        if(hasUnbalancedShard) {
          computeShard(shardCount-1, input.getPEs(), inputTasks, input.PECount(), shardSize, unbalancedShardSize); // If taskCount is divisible for the shardSize, the last shard will be unbalanced.
        }
      }

      // This OMP clausule computes all the balanced shards, which can be all of them or N-1 shards.
      #pragma omp for schedule(static)
      for(unsigned int i = 0; i < shardCount-hasUnbalancedShard; ++i) {
        computeShard(i, input.getPEs(), inputTasks, input.PECount(), shardSize, shardSize); // This is the bulk computation. All shards in this for loop has the same size.
      }
    }
    //########################################################

    //############### Reduction Step #########################
    unsigned int reductionShardCount = shardCount;

    while(reductionShardCount > 0) {
      const unsigned int nextShardCount = reductionShardCount/2;

      #pragma omp parallel firstprivate(reductionShardCount, nextShardCount)
      {
        // This omp clausule treats the special case of the reduction current size is not divisible by 2.
        #pragma omp single nowait
        {
          if(reductionShardCount != 1) {
            if(reductionShardCount%2 > 0)
              shards[0].unionOfTasks(shards[reductionShardCount-1]); // If the reduction count is not multiple of 2, division would not be exact and shards would be cut off from the reduction. This line prevents that by merging the exceeding shard with the shard 0.
            shards[0].unionOfTasks(shards[nextShardCount]);  // Since shard 0 would be unsafe to be written because of this condition, the same thread that computes the extra shard will always compute the shard 0.
          }
        }

        // This omp clausule treats the common case, excluding the shard 0.
        #pragma omp for schedule(static)
        for(unsigned int i = 1; i < nextShardCount; ++i)
          shards[i].unionOfTasks(shards[i+nextShardCount]);
      }

      reductionShardCount = nextShardCount;
    };
    //########################################################

    //############### Populate Output Step ###################

    // The shard 0 will contain all the information after the reduction.
    //After suffering the reduction, the weight values according to the penalized graph have been lost and must be recalculated, since the iterative method would be slower (too much reductions VS few calculations).
    for(unsigned int i = 0; i < input.PECount(); ++i) {
      auto curPE = &(shards[0].mappedPEs[i]);
      curPE->setLoad(penalizedGraphAlgorithm.totalWeightGraph(curPE->load(), curPE->taskCount()));
      strategyOutput.set(&shards[0].mappedPEs[i]);
    }
    //########################################################
  }

};