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

  template<typename ... Concepts>
  WorkloadAware(std::tuple<Concepts...> concepts) : BasicDependencies<TaskWorkload>(std::make_tuple(std::get<0>(concepts))), PE_data(std::get<1>(concepts)) {}
};

/**
 * @brief This class expresses an abstract workload data dependency and a generic K value.
 */
template<typename TaskWorkload, typename PEWorkload, typename K>
struct WorkloadAwareWithK : public WorkloadAware<TaskWorkload, PEWorkload> {
  using Base = WorkloadAware<TaskWorkload, PEWorkload>;

  K *k;

  template<typename ... Concepts>
  WorkloadAwareWithK(std::tuple<Concepts...> concepts) : Base(std::make_tuple(std::get<0>(concepts), std::get<1>(concepts))), k(std::get<2>(concepts)) {}
};

END_NAMESPACE