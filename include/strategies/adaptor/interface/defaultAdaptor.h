#pragma once

#include <system/traits.h>
#include "defaultAdaptorRequirements.h"

/**
 * This class serves as a interface for the adaptor for the input structures, since the input may be brought in by a RTS with it's own semantics.
 * @type DataTypes This type is used to contain the type definitions of Load and Id which are needed inside load balancer strategies. The default typename is the global traits structure.
 */
template<typename DataTypes = Traits<void> >
class DefaultAdaptor {
	static_assert(DefaultAdaptorRequirements<DataTypes>::value, "DataType structure passed to DefaultAdaptor does not meet the static requirements.");
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
  using UInt = typename DataTypes::UInt;

	/**
	 * @return A vector of loads for the PEs
	 */
	virtual std::vector<Load>& PELoads() = 0;

	/**
	 * @return A vector of ids for the PEs.
	 */
	virtual std::vector<Id>& PEIds() = 0;

	/**
	 * @return A vector of loads for the tasks.
	 */
	virtual std::vector<Load>& taskLoads() = 0;

	/**
	 * @return A vector of Ids for the tasks.
	 */
	virtual std::vector<Id>& taskIds() = 0;
};