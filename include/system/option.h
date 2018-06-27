#pragma once

namespace Optional {

template<typename T>
struct Option {
  const bool has;
protected:
  Option(const bool &_has) : has(_has) {}
};

template<typename T>
struct Some : public Option<T> {
  T &value;
  Some(T& _value) : Option<T>(true), value(_value) {}
};

template<typename T>
struct None : public Option<T> {
  None() : Option<T>(false) {}
};

template<typename T>
T& get_value(Option<T> *option) {
  return static_cast<Some<T>*>(option)->value;
}

}