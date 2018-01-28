#pragma once

#include <system/traits.h>

/**
 * @brief This class serves as a interface for the adaptor for the input structures, since the input may be brought in by a RTS with it's own semantics.
 * @type LoadType This type is used to contain the type definition of Load in the library.
 */
template<typename LoadType>
class DefaultAdaptor {
public:

	/**
	 * @type Load The datatype of the load contained in tasks and PEs.
	 */
	using Load = LoadType;

  /**
   * @type UInt The datatype of unsigned integer in the library.
   */
  using UInt = typename Traits<void>::UInt;

	/**
	 * @return A vector of loads for the PEs
	 */
	virtual std::vector<Load>& PELoads() = 0;

	/**
	 * @return A vector of loads for the tasks.
	 */
	virtual std::vector<Load>& taskLoads() = 0;
};