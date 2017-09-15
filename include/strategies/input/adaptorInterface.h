#pragma once

#include <system/traits.h>

/**
 * This class serves as a interface for the adaptor for the input structures, since the input may be brought in by a RTS with it's own semantics.
 * @type DataTypes This type is used to contain the type definitions of Load and Id which are needed inside load balancer strategies. The default typename is the global traits structure.
 */
template<typename DataTypes = Traits<void> >
class AdaptorInterface {
public:

	/**
	 * @type Load The datatype of the load contained in tasks and PEs.
	 */
	using Load = typename DataTypes::Load;
  
  /**
   * @type Id The datatype of the id used to identify PEs and Tasks.
   */
  using Id = typename DataTypes::Id;

  /**
   * @type UInt The unsigned type used in the library.
   */
  using UInt = typename Traits<void>::UInt;

	/**
	 * @param index The index of the PE.
	 * @return The load of the index-th PE present in this input.
	 */
	virtual const Load PELoad(const UInt &index) = 0;

	/**
	 * @param index The index of the PE.
	 * @return The id of the PE.
	 */
	virtual const Id PEId(const UInt &index) = 0;

	/**
	 * @return The ammount of PEs in the library's input.
	 */
	virtual const UInt PECount() = 0;

	/**
	 * @param index The index of the task.
	 * @return The load of the index-th task present in this input.
	 */
	virtual const Load taskLoad(const UInt &index) = 0;

	/**
	 * @param index The index of the task.
	 * @return The id of the task.
	 */
	virtual const Id taskId(const UInt &index) = 0;
	
	/**
	 * @return The ammount of tasks in the library's input.
	 */
	virtual const UInt taskCount() = 0;
};