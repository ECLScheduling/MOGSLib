#pragma once

#include <strategies/impl/greedyPG/greedyPGStrategy.h>

#include "parallelShardGPPG.h"

#include <omp.h>

//#include <iostream> //TODO: Tirar esse include

/**
 * This stategy employs the Greedy and Penalized Graph strategy in a parallel fashion.
 */
class GreedyParallelPGStrategy : public GreedyPenalizedGraphStrategy {

public:

  /**
   * Method to create this strategy with a said penality function.
   */
  GreedyParallelPGStrategy(const PGAlgorithm::PenalityFunction &penalityFunction) : GreedyPenalizedGraphStrategy(penalityFunction) {}

  /**
   * Empty destructor to supress warnings.
   */
  virtual ~GreedyParallelPGStrategy() {}

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Strategy's input.
   */
  virtual void doTaskMapping(const MinimalParallelInput &input) {
    unsigned int PARALLEL_FACTOR = 4;

    unsigned int shardCount = input.taskCount() / (input.PECount()* PARALLEL_FACTOR);
    unsigned int shardSize = input.taskCount() / shardCount;

    ParallelShardGPPG<MinimalParallelInput, GreedyPenalizedGraphStrategy::MinHeap, GreedyPenalizedGraphStrategy::MaxHeap> shards[shardCount](input.PECount());
    //std::cout << "Shards: " << shardCount << " shardSize: " << shardSize << " total: " << shardCount * shardSize << std::endl; //TODO: Tirar isso.

    #pragma omp parallel for schedule(static)
    for(unsigned int i = 0; i < shardCount; ++i) {
      MinimalParallelInput fragmentedInput(input.getPEs(), &(input.getTasks()[i*shardSize]), input.PECount(), shardSize); //TODO: Funciona prq a divisão é exata.

      MaxHeap *tasksHeap = &(shards[i].tasksHeap);
      MinHeap *PEHeap = &(shards[i].PEHeap);
      
      populatePEHeap(fragmentedInput, PEHeap);
      populateTaskHeap(fragmentedInput, tasksHeap);

      executeGreedyStrategy(tasksHeap, PEHeap);
      shards[i].populateOutput(input.getTasks());
    }

    unsigned int reductionShardCount = shardCount;

    while(reductionShardCount > 0) { // TODO: Só funciona se nro de threads é divisivel por 2.
      reductionShardCount /= 2;

      #pragma omp parallel for schedule(static)
      for(unsigned int i = 0; i < reductionShardCount; ++i) {
        shards[i].unionOfTasks(shards[i+reductionShardCount]);
      }
    };
    
    // for(unsigned int i = 0; i < input.PECount(); ++i) {
    //   auto aPE = &shards[0].mappedPEs[i];
    //   std::cout << "PE "<< aPE->id << ": " << aPE->load() << std::endl;
    //   for(auto task : aPE->tasks) {
    //     std::cout << "\tTask " << task->id << ": " << task->load << std::endl;
    //   }
    // }

    populateOutput(shards[0].PEHeap);
  }

};