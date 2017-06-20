#pragma once

#include "penalizedGraphAlgorithm.h"
#include <system/traits.h>
#include <memory>

#include <strategy/input/naiveBasicInput.h>

#include <strategy/abstractStrategy.h>
#include <strategy/impl/greedy/greedyAlgorithm.h>

class GreedyPenalizedGraphStrategy : public AbstractStrategy<NaiveBasicInput> {

protected:
  typedef PenalizedGraphAlgorithm<> PGAlgorithm;
  typedef PenalizedGraphAlgorithmTraits::Graph Graph;
  typedef Graph::Vertex Vertex;
  typedef NaiveBasicInput::Id Id;

  struct PE {
    Graph graph;
    Id id;

    PE(const Id &anId) : id(anId) {
      graph = Graph(id);
    }

    void mapTask(const Vertex &task) {
      graph.addVertex(task);
      graph.setWeight(PGAlgorithm::weightIncrementalGainAVertex(graph, task));
    }
  };

public:
  
  typedef GreedyAlgorithm<Vertex,PE> GreedyAlgorithm;
  typedef GreedyAlgorithm::MaxHeapStructure MaxHeap;
  typedef GreedyAlgorithm::MinHeapStructure MinHeap;

  /**
   * The greedy algorithm that will be used in the strategy.
   */
  GreedyAlgorithm greedyAlgorithm;

  /**
   * The penalized graph algorithm that will be used in the strategy.
   */
  std::unique_ptr<PGAlgorithm> penalizedGraphAlgorithm;

  /**
   * Method to set a penality function to this strategy.
   */
  void setPenalityFunction(const PGAlgorithm::PenalityFunction &penalityFunction) {
    penalizedGraphAlgorithm = std::make_unique<PGAlgorithm>(PGAlgorithm(PenalizedGraphAlgorithmTraits::zeroRef, penalityFunction));
  }

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Load Balancer's input
   */
  virtual void doTaskMapping(const NaiveBasicInput &input) {
    MaxHeap tasks;
    MixHeap PEs;

    //TODO: construct tasks and PEs.

    algorithm.map(tasks, PEs);
    populateOutput(PEs);
  }

protected:

  /**
   * This method is called to populate the output variable lbOutput.
   * @param PEs The heap of PEs modified to contain the tasks by the greedy algorithm.
   */
  void populateOutput(MinHeap &PEs) {
    while(!PEs.empty()) {
      auto _PE = PEs.top();

      for(auto task : PE.tasks()) {
        lbOutput.set(task.id, PE.id);
      }

      PEs.pop();
    }
  }

};