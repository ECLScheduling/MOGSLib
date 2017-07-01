#pragma once

#include <algorithms/penalizedGraph/concepts/penalizedGraphAdaptors.h>

template <typename PEType, typename TaskType>
class AdaptedPE : public GraphAdaptor<TaskType>{
public:

  Load weight(PEType *aPE) {
    return PE.load();
  }

  TaskType* vertices(PEType *aPE) {
    return PE.getTasks();
  }

  unsigned int verticesSize(PEType *aPE) {
    return PE.taskCount();
  }
};