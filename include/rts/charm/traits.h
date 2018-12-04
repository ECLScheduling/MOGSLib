#pragma once

#include <system/traits/rts.h>

namespace MOGSLib { namespace RTS {

/**
 *  @class CharmBaseTraits
 *  @brief The expression of Charm++ minimum traits required by MOGSLib.
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
 *  @class CharmSemantics
 *  @brief A wrapper structure to express the different semantics Charm++ can have for its functionalities.
 */
struct CharmSemantics {
  /**
   *  @class UnavailablePUs
   *  @brief An empty class used for the tag-dispatch technique regarding PU data manipulation semantics.
   *  @tparam filter_unavailable When set to false, will indicate that the platform has only available PUs.
   *
   *  The presense of unavailable PUs alters the Charm++ scheduler semantics as it cannot account assign chares to unavailable PUs.
   *  Algorithms that receive this tag with a true template value must look for and filter unavailable processing elements.
   */
  template<bool filter_unavailable>
  struct UnavailablePUs {};

  /**
   *  @class FixedChares
   *  @brief An empty class used for the tag-dispatch technique regarding chare data manipulation semantics.
   *  @tparam filter_fixed When set to false, will indicate that the application has no fixed chares (all can migrate).
   *
   *  The presense of fixed chares alters the Charm++ scheduler semantics as it cannot schedule these chares for migration.
   *  Algorithms that receive this tag with a true template value must always check if a chare is migratable or not.
   */
  template<bool filter_fixed>
  struct FixedChares {};
};

/**
 *  @class DefaultRuntimeTraits_Charm
 *  @brief A structure to express additional traits required by functionalities in MOGSLib over the Charm++ API.
 *  
 *  Unless intricate customization is to be made, this class should work in any Charm++ centralized load balancer.
 */
template<>
struct DefaultRuntimeTraits<MOGSLib::RuntimeSystemEnum::Charm> : public CharmBaseTraits {
  /// @brief Whether or not MOGSLib functionalities should filter out the unavailable PUs when analyzing the processing units.
  using UnavailablePUs = CharmSemantics::UnavailablePUs<true>;

  /// @brief Whether or not MOGSLib functionalities should filter out the unmigratable chares when analyzing the running chares.
  using FixedChares = CharmSemantics::FixedChares<true>;
};

}}