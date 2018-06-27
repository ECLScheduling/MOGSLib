#pragma once

namespace Optional {

/**
 * @brief A crude implementation of std::optional that will be available only on c++17 STL.
 * @details This implementation is limited as it only stores references, remember to update this snippet when C++17 is stable.
 */
template<typename T>
struct Option {
  const bool has;
protected:
  Option(const bool &_has) : has(_has) {}
};

/**
 * @brief A crude implementation of std::optional to be used when a value is initialized for the optional.
 */
template<typename T>
struct Some : public Option<T> {
  T &value;
  Some(T& _value) : Option<T>(true), value(_value) {}
};

/**
 * @brief A crude implementation of std::optional to be used when a value is not used for the optional.
 */
template<typename T>
struct None : public Option<T> {
  None() : Option<T>(false) {}
};

/**
 * @brief A crude function to get the value of an Option that has a value.
 * @details This function should not be called when the Optional::Option<T> does not have a value. Test with the has member beforehand.
 */
template<typename T>
T& get_value(Option<T> *option) {
  return static_cast<Some<T>*>(option)->value;
}

}