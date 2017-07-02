#pragma once

/**
 * This class is an adaptor to a base PE type. It will provide the functionality of updating the load of an PE by using the PenalizedGraph Algorithm.
 * @type BasePEType A type of PE that this adaptor will wrap.
 * @type PGAlgorithm A concrete type of the PenalizedGraph template, which a pointer will be given to instances of this adaptor.
 */
template<typename BasePEType, typename PGAlgorithm>
class AdaptedPE {
public:

  typedef typename BasePEType::Task Task;

  /**
   * The base PE that this class wraps.
   */
  BasePEType *basePE;

  /**
   * A PenalizedGraphAlgorithm instance pointer.
   */
  PGAlgorithm *penalizedGraphAlgorithm;

  /**
   * An unsafe constructor which does not initializes all the internal state.
   */
  AdaptedPE(){
    allocatedPE = false;
  }

  virtual ~AdaptedPE() {
    if(allocatedPE)
      delete basePE;
  }

  /**
   * Set a base PE to this wrapper class. This class will be responsible for the memory cleaning.
   * @param ptrPE A pointer to a PE instance.
   */
  void setBasePE(BasePEType *ptrPE) {
    basePE = ptrPE;
  }

  /**
   * A method that will wrap the original PE mapTask. This method also updates the load of the wrapped PE, assuming that the PE won't be changed anywhere else.
   */
  void mapTask(Task *task) {
    basePE->setLoad(penalizedGraphAlgorithm->weightIncrementalGainAVertex(basePE->load(), basePE->taskCount(), task->load));
    basePE->mapTask(task);
  }

  const bool operator>(AdaptedPE<BasePEType, PGAlgorithm> other) {
    return *basePE > *(other.basePE);
  }

protected:

  bool allocatedPE;
};