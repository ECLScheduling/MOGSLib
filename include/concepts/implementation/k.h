#pragma once

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concrete concept that serves as a container to a generic K value.
 */
template<typename T = MOGSLib::Index>
struct K {
public:
  T value;
};

/**
 * @brief A concrete concept that serves as a container to a generic K value pointer.
 */
template<typename T = MOGSLib::Index>
struct KPointer {
public:
  T *value;
};

END_NAMESPACE