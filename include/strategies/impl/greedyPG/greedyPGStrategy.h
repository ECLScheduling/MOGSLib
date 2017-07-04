#pragma once

#include <algorithms/penalizedGraph/penalizedGraphAlgorithm.h>
#include <algorithms/greedy/greedyAlgorithm.h>

#include <system/traits.h>

#include <strategies/input/minimalParallelInput.h>
#include <strategies/abstractStrategy.h>

#include "adaptedPE.h"

/**
 * A strategy that uses the greedy algorithm to distribute the load and the penalized graph algorithms to calculate the load.
 */
class GreedyPenalizedGraphStrategy : public AbstractStrategy<MinimalParallelInput> {

public:
  typedef PenalizedGraphAlgorithm<> PGAlgorithm;

  typedef MinimalParallelInput Input;
  typedef typename Input::PE BasePE;
  typedef typename Input::Task Task;
  typedef AdaptedPE<BasePE, PGAlgorithm> PE;
  typedef Task::Id Id;

  /**
   * The penalized graph algorithm that will be used in the strategy.
   */
  PGAlgorithm penalizedGraphAlgorithm;
  
  typedef GreedyStrategyAlgorithm<Task, PE> GreedyAlgorithm;
  typedef GreedyAlgorithm::MaxHeap MaxHeap;
  typedef GreedyAlgorithm::MinHeap MinHeap;

  /**
   * Method to create this strategy with a said penality function
   */
  GreedyPenalizedGraphStrategy(const PGAlgorithm::PenalityFunction &penalityFunction) : penalizedGraphAlgorithm(Traits<void>::zeroRef, penalityFunction) {}

  virtual ~GreedyPenalizedGraphStrategy() {}

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the strategyOutput variable.
   * @param input The Load Balancer's input
   */
  virtual void doTaskMapping(const Input &input) {
    MaxHeap tasks;
    MinHeap PEs;

    populatePEHeap(input, &PEs);
    populateTaskHeap(input, &tasks);

    executeGreedyStrategy(&tasks, &PEs);
    
    while(!PEs.empty()) {
      auto _PE = PEs.top().basePE;
      auto tasks = _PE->tasks;

      strategyOutput.set(_PE);
      PEs.pop();
    }
  }

protected:

  /**
   * The implementation of the strategy, which is executing the greedy strategy with the mapped graph and container objects.
   * @param taskHeap The pointer to the MaxHeap of tasks.
   * @param PEHeap The pointer to the MinHeap of PEs.
   */
  virtual void executeGreedyStrategy(MaxHeap *taskHeap, MinHeap *PEHeap) {
    GreedyAlgorithm greedyAlgorithm;

    greedyAlgorithm.map(*taskHeap, *PEHeap);
  }

  /**
   * Adds all the tasks to the task heap so they can be used on the greedy algorithm.
   */
  virtual void populateTaskHeap(const Input &input, MaxHeap *taskHeap) {
    auto tasks = input.getTasks();

    for(unsigned int i = 0; i < input.taskCount(); ++i)
      taskHeap->push(&tasks[i]);
  }

  /**
   * Adds all the PEs in the heap for using it on greedy algorithm.
   */
  virtual void populatePEHeap(const Input &input, MinHeap *PEHeap) {
    auto _PE = input.getPEs();

    for(unsigned int i = 0; i < input.PECount(); ++i) {
      PE adaptedPE;
      adaptedPE.setBasePE(new BasePE(_PE[i].id)); //TODO: In future changes, make the inputs only contain blueprints of PEs, instead of full objects that are going to be copied.
      adaptedPE.penalizedGraphAlgorithm = &penalizedGraphAlgorithm;
    
      PEHeap->push(adaptedPE);
    }
  }

};