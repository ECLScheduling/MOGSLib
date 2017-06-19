#pragma once

#include "penalizedGraphAlgorithm.h"
#include <system/types>

#include <../greedy/greedyAlgorithm.h>
#include <strategy/loadBalancer.h>

template<typename Graph = EdgelessGraph, typename Vertex = EdgelessVertex, typename Weight = EdgelessGraph::Weight, typename InputType = NaiveBasicInput>
class GreedyPenalizedGraphStrategy : public LoadBalancer<InputType> {

public:
  typedef GreedyLoadBalancerAlgorithm<Vertex, Graph>  GreedyAlgorithm;
  typedef GreedyAlgorithm::MaxHeapStructure MaxHeap;
  typedef GreedyAlgorithm::MinHeapStructure MinHeap;

  GreedyAlgorithm algorithm;

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Load Balancer's input
   */
  virtual void doTaskMapping(const InputType &input) {
    MaxHeap tasks;
    MaxHeap PEs;

    algorithm.map(tasks, PEs);

    while(!PEs.empty()) {
      auto PE = PEs.top();

      for(auto task : PE.tasks()) {
        lbOutput.set(task.id, PE.id);
      }

      PEs.pop();
    }
  }

};