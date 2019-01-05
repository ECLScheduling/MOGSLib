#pragma once

#include <vector>

#include "functionalities.h"

#define CHARM_RTS_INCLUDED

namespace MOGSLib { namespace RTS {

/**
 *  @class Charm
 *  @brief Declaration of specific types and core functionalities exposed by the Charm++ runtime system.
 *  @tparam Traits A traits structure to guide Charm functionalities, see reference in <tt>DefaultRuntimeTraits_Charm</tt>.
 */
struct Charm {
  
  /// @brief Id type is defined by the Traits parameter.
  using Id = typename Traits::Id;
  /// @brief Load type is defined by the Traits parameter.
  using Load = typename Traits::Load;

  /// @brief LDStats type is defined by Charm++ CentralLB structure.
  /// @details This header must be included after including a definition of the LDStats type.
  using LDStats = BaseLB::LDStats*;
  
  /// @brief Variables to keep track of Charm++ chares and PU ids.
  /// @details These ids must be retrieved to apply the chare mapping generated by MOGSLib into Charm++.
  static std::vector<Id> chare_ids, pu_ids;
  
  /// @brief A pointer to the load balancer data within the Charm++ runtime system.
  static LDStats stats;

  /// @brief A representation of the Charm++ LBDB structure capabilities.
  struct LBDB {
    /// @brief A concrete definition of the CharmFunctionalities with correct values for index and load.
    using Helper = CharmFunctionalities<Id, Load>;

    /// @brief A representation of the Charm++ LBDB functions regarding the manipulation of PU data.
    struct PU {

      /**
       *  @brief Get the amount of PUs in the Charm++ system.
       *  @return The amount of PUs in the execution platform.
       * 
       *  This function yields different semantics depending on the Charm Traits.
       *  It may or may not ignore PUs availability status based on the check_for_unavailable_pus trait.
       */
      static inline Id count();

      /**
       *  @brief Get the PUs predicted load based on background load and fixed chares.
       *  @return A vector of loads associated to the execution platform's PUs.
       *
       *  This method must be called after PU::count.
       *  It searches only the PUs whose ids are in Charm::pu_ids.
       */
      static inline std::vector<Load> load_prediction();
    };

    /// @brief A representation of the LBDB capabilities for the manipulation of chare data.
    struct Chare {
      /**
       *  @brief Get the amount of chares in the Charm++ system.
       *  @return The amount of chares in the running application.
       *
       *  This function yields different semantics depending on Charm Traits.
       *  It may or may not ignore chare migratability status based on the check_for_fixed_chares trait.
       */
      static inline Id count();

      /**
       *  @brief Get the chares predicted load based on the processor speed and time to complete on previous iterations.
       *  @return A vector of loads associated to the application's chares.
       *
       *  This method must be called after Chare::count.
       *  Iit searches only the task whose ids are in Charm::chare_ids.
       */
      static inline std::vector<Load> load_prediction();
    };
  };
};

}}