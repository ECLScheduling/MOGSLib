#pragma once

namespace MOGSLib { namespace Concept {

/**
 * \brief A concrete concept that serves as a container to a generic K value.
 */
template<typename T = MOGSLib::Index>
struct K {
public:
  T value;
};

}}