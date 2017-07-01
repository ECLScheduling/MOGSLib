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
  ParallelShardGPPG(unsigned int PESize) {
    _PESize = PESize;
    mappedPEs = new PE[_PESize];
  }

  /**
   * A deconstructor that destroys the local view of the PEs.
   */
  virtual ~ParallelShardGPPG() {
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
  void unionOfTasks(const ParallelShardGPPG<InputType, MinHeap, MaxHeap> &other) {
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