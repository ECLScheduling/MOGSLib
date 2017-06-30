#pragma once

#include "greedyPGStrategy.h"

#include <omp.h>

#include <iostream>

class ParallelShard {
public:
  unsigned int _PESize;

public:
  typedef MinimalParallelInput::PE PE;
  typedef MinimalParallelInput::Task Task;
  typedef GreedyPenalizedGraphStrategy::MinHeap MinHeap;
  typedef GreedyPenalizedGraphStrategy::MaxHeap MaxHeap;

  PE *mappedPEs;
  MaxHeap tasksHeap;
  MinHeap PEHeap;

  ParallelShard(unsigned int PESize) {
    _PESize = PESize;
    mappedPEs = new PE[_PESize];
  }

  virtual ~ParallelShard() {
    delete[] mappedPEs;
  }

  void populateOutput(Task *taskRef) {

    for(unsigned int i = 0; i < _PESize; ++i) {
      auto _PE = PEHeap.top();
      auto tasks = _PE.tasks();

      PEHeap.pop();
      mappedPEs[_PE.id].id = _PE.id; //TODO: Funciona prq os PEs são criados assim, em sequência.
      
      for(int j = 0; j < _PE.taskCount(); ++j) {
        mappedPEs[_PE.id].mapTask(&taskRef[tasks[j].id]); //TODO: Funciona prq as tasks foram criadas assim, em sequencia.
      }

      mappedPEs[_PE.id].setLoad(_PE.graph.weight()); //TODO: Da de fazer melhor
    }
  }
  
};

/**
 * This stategy employs the Greedy and Penalized Graph strategy in a parallel fashion.
 */
class GreedyParallelPGStrategy : public GreedyPenalizedGraphStrategy {

public:

  /**
   * Method to create this strategy with a said penality function
   */
  GreedyParallelPGStrategy(const PGAlgorithm::PenalityFunction &penalityFunction) : GreedyPenalizedGraphStrategy(penalityFunction) {}

  virtual ~GreedyParallelPGStrategy() {}

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Strategy's input
   */
  virtual void doTaskMapping(const MinimalParallelInput &input) {
    unsigned int shardCount = input.taskCount() / (input.PECount()*8);
    unsigned int shardSize = input.taskCount() / shardCount;

    ParallelShard shards[shardCount](input.PECount());
    std::cout << "Shards: " << shardCount << " shardSize: " << shardSize << " total: " << shardCount * shardSize << std::endl; 

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

    populateOutput(shards[0].PEHeap);
  }

};