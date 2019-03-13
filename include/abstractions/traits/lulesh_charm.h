#pragma once

#include <abstractions/rts/charm/traits.h>

struct LuleshCharm {
  using Id = typename MOGSLib::SystemTraits<MOGSLib::System::charm>::Id;
  using Load = typename MOGSLib::SystemTraits<MOGSLib::System::charm>::Load;

  using UnavailablePUs = typename MOGSLib::CharmSemantics::UnavailablePUs<true>;
  using RigidJobs = typename MOGSLib::CharmSemantics::RigidJobs<true>;
};