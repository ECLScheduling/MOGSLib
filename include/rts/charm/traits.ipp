#pragma once

#include <system/traits/rts.h>

namespace MOGSLib {

/**
 *  @class CharmBaseTraits
 *  @brief The expression of Charm++ minimum traits for MOGSLib.
 *  
 *  Unless intricate customization is to be made, this class should work in any Charm++ centralized load balancer.
 */
struct CharmBaseTraits {
  
  /// @brief The type definition that will serve as index in MOGSLib when used in Charm++.
  using Index = decltype(BaseLB::LDStats::n_objs);

  /// @brief The type definition that will serve to quantify load values in MOGSLib when used in Charm++.
  using Load = decltype(BaseLB::ProcStats::bg_walltime);

  /// @brief The name of the system so it can be referenced on user-friendly messages.
  static constexpr auto name = "Charm++";
};

/**
 *  @class DefaultRuntimeTraits_Charm
 *  @brief A structure to express additional traits required by functionalities in MOGSLib over the Charm++ API.
 *  
 *  Unless intricate customization is to be made, this class should work in any Charm++ centralized load balancer.
 */
template<>
struct DefaultRuntimeTraits<RuntimeSystemEnum::Charm> : public CharmBaseTraits {
  /// @brief Whether or not MOGSLib functionalities should filter out the unavailable PUs when analyzing the processing units.
  static constexpr auto check_for_unavailable_pus = true;

  /// @brief Whether or not MOGSLib functionalities should filter out the unmigratable chares when analyzing the running chares.
  static constexpr auto check_for_fixed_chares = true;
};

}