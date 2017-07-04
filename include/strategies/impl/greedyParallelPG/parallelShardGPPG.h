#pragma once

/**
 * A class that will wrap the context of execution of threads that will compute bits of the Greedy Penalized Graph. 
 */
template <typename InputType, typename MinHeap, typename MaxHeap>
class ParallelShardGPPG {
protected:

  /**
   * The ammount of PEs in the input.
   */
  unsigned int _PESize;

public:

  typedef typename InputType::PE PE;
  typedef typename InputType::Task Task;
  typedef typename Task::Load Load;

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
   * An unsafe constructor that doesn't initialize the internal state. This constructor is needed due to the nature of this object which will be created by new [].
   */
  ParallelShardGPPG() {
    allocatedPE = false;
  }

  /**
   * A deconstructor that destroys the local view of the PEs.
   */
  virtual ~ParallelShardGPPG() {
    destroyAllocatedPE();
  }

  /**
   * Allocated the array of local PEs used in this shard.
   * @details This method needs to be called before any operation on this class. 
   * @param PECount The total ammount of PEs the input to the strategy has.
   */
  void setPECount(unsigned int PECount) {
    destroyAllocatedPE();
    _PESize = PECount;
    mappedPEs = new PE[_PESize];
  }

  /**
   * A method that must be called after all the operations over the heaps are made to modify the PE elements.
   * @details This method moves information from the heaps, that should be used by outter algorithm classes, to the local-view array of PEs.
   * @param taskRef This is a pointer to the global array of tasks. This parameter is relevant to avoid duplicating the task information in memory.
   */
  void populateOutput(Task *taskRef) {

    for(unsigned int i = 0; i < _PESize; ++i) {
      Load loadSum = 0;
      PE* _PE = PEHeap.top().basePE;
      auto tasks = _PE->tasks;

      PEHeap.pop();
      mappedPEs[_PE->id].id = _PE->id;
      
      for(auto task : tasks) {
        mappedPEs[_PE->id].mapTask(task);
        loadSum += task->load;
      }

      // Load is set to the sum of the loads to pre-calculate the final weight of the graph, which is not visible to this container object.
      mappedPEs[_PE->id].setLoad(loadSum);
    }
  }

  /**
   * A method that combines the tasks of two ParallelShards. This method is used to make a reduction over an array of shards.
   * @details Both parallel shards will have their mapped tasks merged by combining the local view of PEs.
   * @param other The other ParallelShard that will have it's mapped tasks aggregated.
   */
  void unionOfTasks(const ParallelShardGPPG<InputType, MinHeap, MaxHeap> &other) {
    for(unsigned int i = 0; i < _PESize; ++i) {
      auto otherPE = &other.mappedPEs[i];
      auto thisPE = &mappedPEs[i];

      for(auto task : otherPE->tasks) {
        thisPE->mapTask(task);
      }
      
      thisPE->setLoad(thisPE->load() + otherPE->load());
    }
  }
  
  protected:

    bool allocatedPE;

  /**
   * Destroy the local data of the PEs.
   */
  void destroyAllocatedPE() {
    if(allocatedPE) {
      delete[] mappedPEs;
      allocatedPE = false;
    }
  }
  
};