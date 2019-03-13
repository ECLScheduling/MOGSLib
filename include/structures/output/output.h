#pragma once

#include <vector>

namespace MOGSLib {

template<typename Out>
struct Output {};

template<typename Id>
struct Output<std::vector<Id>> {
  static inline std::vector<Id> alloc(const Id &n) {
    std::vector<Id> v;
    v.resize(n);
    return std::move(v);
  }

  static inline void clear(std::vector<Id> out) {
    out.clear();
  }

  static inline void destroy(std::vector<Id> &n) {
    n.clear();
  }
};

template<typename Id>
struct Output<Id*> {
  static inline Id* alloc(const Id &n) {
    return new Id[n]();
  }

  static inline void clear(Id* out) {}

  static inline void destroy(Id* n) {
    delete [] n;
  }
};

}