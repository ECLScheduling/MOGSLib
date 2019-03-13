#pragma once

#include <structures/input/workload_aware.h>

#include <abstractions/rts/charm/charm.h>

namespace MOGSLib { namespace Context {

struct Charm {
  using Id = typename Traits::Id;
  using Load = typename Traits::Load;

  MOGSLib::Input::WorkloadAware<Id, Load> _input;

protected:
  inline void update_tasks() {
    MOGSLib::RTS::Charm::LBDB::Chare::count();
    MOGSLib::RTS::Charm::LBDB::Chare::load_prediction(_input.tasks);
  }

  inline void update_pus() {
    MOGSLib::RTS::Charm::LBDB::PU::count();
    MOGSLib::RTS::Charm::LBDB::PU::load_prediction(_input.pus);
  }

public:

  inline auto& input() {
    update_tasks();
    update_pus();
    return _input;
  }
};

}}