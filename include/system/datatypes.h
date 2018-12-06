#pragma once

#include <vector>

namespace MOGSLib {

/**
 *  @class PolicyTypedef
 *  @tparam I the Index type definition.
 *
 *  A structure to wrap the minimum necessary types for any non-specialized scheduling policy.
 */
template<typename I>
struct PolicyTypedef {
  using Index = I;
  using Schedule = std::vector<Index>;
};

/**
 *  @class WorkloadPolicyTypedef
 *  @tparam I the Index type definition.
 *  @tparam L the Load type definition.
 *
 *  A structure to wrap the minimum necessary types for workload aware scheduling policy.
 */
template<typename I, typename L>
struct WorkloadPolicyTypedef : public PolicyTypedef<I> {
  using Load = L;
};

/**
 *  @class TypeDefinition
 *  @tparam PolicyDef The definitions associated with the base scheduling policy.
 *  @tparam Others Other definitions meant to be specialized.
 *
 *  A structure to wrap all type definitions for the scheduling solution.
 */
template<typename PolicyDef, typename ... Others>
struct TypeDefinition {
  using Policy = PolicyDef;
};

}