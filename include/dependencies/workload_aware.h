#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Dependency)

template<typename ... Concepts>
struct WorkloadAware {
  using DependencyTuple = std::tuple<Concepts ...>;
  using pDependencyTuple = std::tuple<Concepts *...>;

  typename std::tuple_element<0, DependencyTuple>::type *task_data;
  typename std::tuple_element<1, DependencyTuple>::type *PE_data;

  WorkloadAware(pDependencyTuple concepts) : task_data(std::get<0>(concepts)), PE_data(std::get<1>(concepts)) {}
};

template<typename ... Concepts>
struct WorkloadAwareWithK : public WorkloadAware<Concepts ...> {
  using Parent = WorkloadAware<Concepts ...>;

  typename std::tuple_element<2, typename Parent::DependencyTuple>::type *k_data;

  WorkloadAwareWithK(typename Parent::pDependencyTuple concepts) : Parent(concepts), k_data(std::get<2>(concepts)) {}
};

END_NAMESPACE