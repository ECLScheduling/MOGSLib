#pragma once

namespace MOGSLib { namespace Concept {

/**
 *  @brief A container concept to access generic K values.
 *  @tparam T The type of value for k.
 *
 *  Preferably extend this concept, as K is meant to be generic, thus not a very informative concept.
 */
template<typename T>
struct K {
public:
  T value;
};

}}