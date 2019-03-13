#pragma once

#include <mogslib/constants.h>

namespace MOGSLib {

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
   *  @class RigidJobs
   *  @brief An empty class used for the tag-dispatch technique regarding chare data manipulation semantics.
   *  @tparam filter_fixed When set to false, will indicate that the application has no fixed chares (all can migrate).
   *
   *  The presense of fixed chares alters the Charm++ scheduler semantics as it cannot schedule these chares for migration.
   *  Algorithms that receive this tag with a true template value must always check if a chare is migratable or not.
   */
  template<bool filter_fixed>
  struct RigidJobs {};
};

template<>
struct SystemTraits<System::charm> {
  /// @brief The type definition that will serve as index in MOGSLib when used in Charm++.
  using Id = decltype(BaseLB::LDStats::n_objs);

  /// @brief The type definition that will serve to quantify load values in MOGSLib when used in Charm++.
  using Load = decltype(BaseLB::ProcStats::bg_walltime); // LBRealType
};

}