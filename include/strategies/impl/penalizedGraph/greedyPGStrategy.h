#pragma once

#include "penalizedGraphAlgorithm.h"
#include <system/traits.h>

#include <strategies/input/naiveBasicInput.h>

#include <strategies/abstractStrategy.h>
#include <strategies/impl/greedy/greedyAlgorithm.h>

/**
 * A strategy that uses the greedy algorithm to distribute the load and the penalized graph algorithms to calculate the load.
 */
class GreedyPenalizedGraphStrategy : public AbstractStrategy<NaiveBasicInput> {

public:
  typedef PenalizedGraphAlgorithm<> PGAlgorithm;
  typedef PenalizedGraphAlgorithmTraits::Graph Graph;
  typedef Graph::Vertex Vertex;
  typedef NaiveBasicInput::Id Id;


  /**
   * The penalized graph algorithm that will be used in the strategy.
   */
  PGAlgorithm penalizedGraphAlgorithm;

  /**
   * Auxiliary PE structure to wrap the graph, adding the mapTask functionallity needed by GreedyAlgorithm.
   */
  struct PE {

    /**
     * The wrapped graph structure.
     */
    Graph graph;

    /**
     * The PE id, which is the same as the graph id.
     * @note This cannot be a pointer as the greedy uses id value, not reference.
     */
    Id id;

    /**
     * The reference to the PenalizedGraphAlgorithm instance used to calculate the weight of the PE.
     */
    const PGAlgorithm * pgAlgorithm;

    PE(const Id &anId, const PGAlgorithm *pgAlgorithmRef) : id(anId), pgAlgorithm(pgAlgorithmRef) {
      graph = Graph(id);
    }

    /**
     * A function that is called on the GeedyStrategy when the algorithm decides where a task will be located.
     */
    void mapTask(const Vertex &task) {
      graph.addVertex(task);
      graph.setWeight(pgAlgorithm->weightIncrementalGainAVertex(graph, task.weight()));
    }

    /**
     * Proxy function to get the vertices of the graph, which are the tasks of this PE wrapper structure.
     */
    inline Vertex * tasks() {
      return graph.vertices();
    }

    /**
     * Proxy function to get the vertices count of the graph, which are the tasks count of this PE wrapper structure.
     */
    inline const int taskCount() {
      return graph.verticesSize();
    }

    /**
     * A forwarded greater than comparator.
     */
    const bool operator>(const PE &o) const {
      return graph > o.graph;
    }
    
  };
  
  typedef GreedyStrategyAlgorithm<Vertex,PE> GreedyAlgorithm;
  typedef GreedyAlgorithm::MaxHeap MaxHeap;
  typedef GreedyAlgorithm::MinHeap MinHeap;

  /**
   * Method to create this strategy with a said penality function
   */
  GreedyPenalizedGraphStrategy(const PGAlgorithm::PenalityFunction &penalityFunction) : penalizedGraphAlgorithm(PenalizedGraphAlgorithmTraits::zeroRef, penalityFunction) {}

  virtual ~GreedyPenalizedGraphStrategy() {}

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Load Balancer's input
   */
  virtual void doTaskMapping(const NaiveBasicInput &input) {
    MaxHeap tasks;
    MinHeap PEs;

    populatePEHeap(input, &PEs);
    populateTaskHeap(input, &tasks);

    executeGreedyStrategy(&tasks, &PEs);
    populateOutput(PEs);
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

  virtual void populateTaskHeap(const NaiveBasicInput &input, MaxHeap *taskHeap) {
    auto taskIds = input.getTasksIds();

    for(auto taskId : taskIds)
      taskHeap->push(Vertex(taskId, input.getTaskLoad(taskId)));
  }

  virtual void populatePEHeap(const NaiveBasicInput &input, MinHeap *PEHeap) const {
    auto PEIds = input.getPEsIds();

    for(auto id : PEIds)
      PEHeap->push(PE(id, &penalizedGraphAlgorithm));
  }

  /**
   * This method is called to populate the output variable lbOutput.
   * @param PEs The heap of PEs modified to contain the tasks by the greedy algorithm.
   */
  virtual void populateOutput(MinHeap &PEs) {
    while(!PEs.empty()) {
      auto _PE = PEs.top();
      auto tasks = _PE.tasks();

      for(auto i = 0; i < _PE.taskCount(); ++i) {
        lbOutput.set(tasks[i].id, _PE.id);
      }

      PEs.pop();
    }
  }

};