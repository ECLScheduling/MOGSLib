#pragma once

#include <system/traits.h>
#include <precompiler/input/all.h>


template<>
struct Defaults<GreedyScheduler> {

  using ApplicationData = Input::MinimalApplicationData;
  using PlatformData = Input::MinimalPlatformData;
  using MiscData = Concepts::NoMiscData;

  using Input = Concepts::SchedulerInput<ApplicationData, PlatformData, MiscData>;
};