#pragma once

namespace Concepts {

/**
 * @brief A class that serves the purpose of represening the absence of platform data for the scheduler at compile time.
 */
struct NoPlatformData {};

/**
 * @brief A class that serves the purpose of represening the absence of platform's resource data for the scheduler at compile time.
 */
struct NoResourceData {};

/**
 * @brief A class that declares the conceptual platform data.
 * @type ResourceData The type that wraps the platform's resources data.
 */
template<typename ResourceData = NoResourceData>
struct PlatformData {
  ResourceData resources;
};

}