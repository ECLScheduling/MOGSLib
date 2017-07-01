#pragma once

#include "greedyPGStrategy.h"

#include <omp.h>

#include <iostream> //TODO: Tirar esse include

/**
 * A class that will wrap the context of execution of threads that will compute bits of the Greedy Penalized Graph. 
 */
class ParallelShard {
protected:

  /**
   * The ammount of PEs in the input.
   */
  unsigned int _PESize;

public:
  typedef MinimalParallelInput::PE PE;
  typedef MinimalParallelInput::Task Task;
  typedef GreedyPenalizedGraphStrategy::MinHeap MinHeap;
  typedef GreedyPenalizedGraphStrategy::MaxHeap MaxHeap;

  /**
   * An array of PEs. This is a local variable.
   */
  PE *mappedPEs;

  /**
   * A max heap that will be used outside of this class scope, but must be stored in a thread context.
   */
  MaxHeap tasksHeap;
  
  /**
   * A min heap that will be used outside of this class scope, but must be stored in a thread context.
   */
  MinHeap PEHeap;

  /**
   * A constructor that allocates but does not initialize the local view of the PEs.
   */
  ParallelShard(unsigned int PESize) {
    _PESize = PESize;
    mappedPEs = new PE[_PESize];
  }

  /**
   * A deconstructor that destroys the local view of the PEs.
   */
  virtual ~ParallelShard() {
    delete[] mappedPEs;
  }

  /**
   * A method that must be called after all the operations over the heaps are made to modify the PE elements.
   * @details This method moves information from the heaps, that should be used by outter algorithm classes, to the local-view array of PEs.
   * @param taskRef This is a pointer to the global array of tasks. This parameter is relevant to avoid duplicating the task information in memory.
   */
  void populateOutput(Task *taskRef) {

    for(unsigned int i = 0; i < _PESize; ++i) {
      auto _PE = PEHeap.top();
      auto tasks = _PE.tasks();

      PEHeap.pop();
      mappedPEs[_PE.id].id = _PE.id; //NOTE: Funciona prq os PEs são criados assim, em sequência.
      
      for(int j = 0; j < _PE.taskCount(); ++j) {
        mappedPEs[_PE.id].mapTask(&taskRef[tasks[j].id]); //NOTE: Funciona prq as tasks foram criadas assim, em sequencia.
      }

      mappedPEs[_PE.id].setLoad(_PE.graph.weight()); //TODO: Da de fazer melhor
    }
  }

  /**
   * A method that combines the tasks of two ParallelShards. This method is used to make a reduction over an array of shards.
   * @details Both parallel shards will have their mapped tasks merged by combining the local view of PEs.
   * @param other The other ParallelShard that will have it's mapped tasks aggregated.
   */
  void unionOfTasks(const ParallelShard &other) {
    for(unsigned int i = 0; i < _PESize; ++i) {
      auto otherPE = &other.mappedPEs[i];
      auto thisPE = &mappedPEs[i];

      for(auto task : otherPE->tasks) {
        thisPE->mapTask(task);
      }

      thisPE->setLoad(thisPE->load() + otherPE->load()); //TODO: Ainda teria que fazer o calculo da penalidade
    }
  }
  
};

/**
 * This stategy employs the Greedy and Penalized Graph strategy in a parallel fashion.
 */
class GreedyParallelPGStrategy : public GreedyPenalizedGraphStrategy {

public:

  /**
   * Method to create this strategy with a said penality function.
   */
  GreedyParallelPGStrategy(const PGAlgorithm::PenalityFunction &penalityFunction) : GreedyPenalizedGraphStrategy(penalityFunction) {}

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

    ParallelShard shards[shardCount](input.PECount());
    std::cout << "Shards: " << shardCount << " shardSize: " << shardSize << " total: " << shardCount * shardSize << std::endl; //TODO: Tirar isso.

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
    
    for(unsigned int i = 0; i < input.PECount(); ++i) {
      auto aPE = &shards[0].mappedPEs[i];
      std::cout << "PE "<< aPE->id << ": " << aPE->load() << std::endl;
      for(auto task : aPE->tasks) {
        std::cout << "\tTask " << task->id << ": " << task->load << std::endl;
      }
    }

    populateOutput(shards[0].PEHeap);
  }

};