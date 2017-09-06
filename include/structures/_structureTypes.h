#pragma once

//#######################################################
// This header is used to pre-declare usable structures implemented in the library.
//#######################################################

template<typename IdType, typename LoadType>
class SimpleTask;

template<typename TaskType>
class SimplePE;

template<typename IndexType, typename ValueType>
class Matrix1D;

namespace EagerMap {

  class TopologyData;
  class TaskGroup;
  class CommunicationMatrix;
}