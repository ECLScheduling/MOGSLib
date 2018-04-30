#pragma once

#include <precompiler/all_input_concepts.h>

namespace Concepts {

/**
 * @brief A class that declares the conceptual scheduler input.
 * @type AppData The type that wraps the application data.
 * @type PlatformData The type that wraps the platform data.
 * @type MiscData The type that wraps miscellaneous data for scheduler decisions that does not belong to other categories of data.
 */
template<typename AppData = NoApplicationData, typename PlatformData = NoPlatformData, typename MiscData = NoMiscData>
struct SchedulerInput {
  AppData app;
  PlatformData platform;
  MiscData misc;
};

template<typename PlatformData, typename MiscData>
struct SchedulerInput<NoApplicationData, PlatformData, MiscData> {
  PlatformData platform;
  MiscData misc;
};

template<typename AppData, typename MiscData>
struct SchedulerInput<AppData, NoPlatformData, MiscData> {
  AppData app;
  MiscData misc;
};

template<typename AppData, typename PlatformData>
struct SchedulerInput<AppData, PlatformData, NoMiscData> {
  AppData app;
  PlatformData platform;
};

template<typename AppData>
struct SchedulerInput<AppData, NoPlatformData, NoMiscData> {
  AppData app;
};

template<typename PlatformData>
struct SchedulerInput<NoApplicationData, PlatformData, NoMiscData> {
  PlatformData platform;
};

template<typename MiscData>
struct SchedulerInput<NoApplicationData, NoPlatformData, MiscData> {
  MiscData misc;
};

template<>
struct SchedulerInput<NoApplicationData, NoPlatformData, NoMiscData> {};

}