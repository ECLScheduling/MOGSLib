#pragma once

#include <system/static.h>
#include <dependencies/basic.h>

BEGIN_NAMESPACE(Dependency)

/**
 * @brief This class expresses an abstract workload data dependency.
 * @details TODO: When C++17 comes out, change the typenames for Concepts and add the necessary methods to obtain workloads.
 */
template<typename TaskWorkload, typename PEWorkload>
struct WorkloadAware : public BasicDependencies<TaskWorkload> {
  PEWorkload *PE_data;

  WorkloadAware(std::tuple<TaskWorkload*, PEWorkload*> c) : BasicDependencies<TaskWorkload>(std::make_tuple(std::get<0>(c))), PE_data(std::get<1>(c)) {}
};

/**
 * @brief This class expresses an abstract workload data dependency and a generic K value.
 */
template<typename TaskWorkload, typename PEWorkload, typename K>
struct WorkloadAwareWithK : public WorkloadAware<TaskWorkload, PEWorkload> {
  K *k;

  WorkloadAwareWithK(std::tuple<TaskWorkload*, PEWorkload *, K*> c) : WorkloadAware<TaskWorkload, PEWorkload>(std::make_tuple(std::get<0>(c), std::get<1>(c))), k(std::get<2>(c)) {}
};

END_NAMESPACE