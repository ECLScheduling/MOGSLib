#pragma once

#include <dependencies/minimal_dependencies.h>

namespace MOGSLib { namespace Dependency {

/**
 * \brief This class expresses an abstract workload data dependency.
 * @details TODO: When C++17 comes out, change the typenames for Concepts and add the necessary methods to obtain workloads.
 */
template<typename TaskWorkload, typename PEWorkload>
struct WorkloadAware : public MinimalDependencies<TaskWorkload> {
  PEWorkload *PE_data;

  WorkloadAware(std::tuple<TaskWorkload*, PEWorkload*> concepts) : MinimalDependencies<TaskWorkload>(std::make_tuple(std::get<0>(concepts))), PE_data(std::get<1>(concepts)) {}
};

/**
 * \brief This class expresses an abstract workload data dependency and a generic K value.
 */
template<typename TaskWorkload, typename PEWorkload, typename K>
struct WorkloadAwareWithK : public WorkloadAware<TaskWorkload, PEWorkload> {
  K *k;

  WorkloadAwareWithK(std::tuple<TaskWorkload*, PEWorkload*, K*> concepts) : WorkloadAware<TaskWorkload, PEWorkload>(std::make_tuple(std::get<0>(concepts), std::get<1>(concepts))), k(std::get<2>(concepts)) {}
};

}}