#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Dependency)

/**
 * @brief This class expresses an abstract workload data dependency.
 */
template<typename TaskWorkload, typename PEWorkload>
struct WorkloadAware {
  TaskWorkload *task_data;
  PEWorkload *PE_data;

  template<typename ... Concepts>
  WorkloadAware(std::tuple<Concepts...> concepts) : task_data(std::get<0>(concepts)), PE_data(std::get<1>(concepts)) {}
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