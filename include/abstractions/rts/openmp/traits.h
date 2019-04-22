#pragma once

#include <mogslib/constants.h>

namespace MOGSLib {

/**
 * @brief The system traits when using MOGSLib on OpenMP
 */
template<>
struct SystemTraits<System::libgomp> {
  using Id = unsigned;
  using Load = unsigned;
};

namespace RTS {
  using LibGOMPTraits = MOGSLib::SystemTraits<MOGSLib::System::libgomp>;
}

}