#pragma once

#include <algorithms/penalizedGraph/penalizedGraphAdaptors.h>

/**
 * This class wraps a Task object and adapts it to be used in the PenalizedGraphAlgorithm.
 * @type Task The task type that is wrapped by this class must contain a Load definition and a load member.
 */
template<typename Task>
class AdaptedTask : public PenalizedGraphConcepts::VertexAdaptor<typename Task::Load> {
public:

  /**
   * The task component of this adaptor.
   */
  Task *task;

  /**
   * An unsafe constructor that does not initializes internal state.
   * @details This constructor makes possible to create static arrays of this class, but it must be used cautiously.
   */
  AdaptedTask() {}

  /**
   * A safe constructor that initialized internal state. 
   */
  AdaptedTask(Task *aTask) {
    task = aTask;
  }

  /**
   * The adapted weight method, declared in the VertexAdaptor.
   * @return The load of the task component.
   */
  Load weight() {
    return task->load;
  }
};