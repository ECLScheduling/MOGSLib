#pragma once

#include <iostream>
#include <system/traits.h>

class Debug {
public:
  
  template<typename T>
  Debug& operator<< (const T &p) {
    std::cout << p;
    return *this;
  }
};

class No_Debug {
public:

  template<typename T>
  No_Debug& operator<< (const T &o) {
    return *this;
  }
};

template<bool debugging>
class Selected_Debug : public Debug {};

template<>
class Selected_Debug<false> : public No_Debug {};


enum Debug_Error {error = 1};

template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::error)> debug(Debug_Error e) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::error>() << "[ERR]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::error>();
}

enum Debug_Warning {warning = 2};

template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::warning)> debug(Debug_Warning w) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::warning>() << "[WRN]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::warning>();
}

enum Debug_Info {info = 3};

template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::info)> debug(Debug_Info i) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::info>() << "[INF]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::info>();
}

enum Debug_Trace {trace = 4};

template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::trace)> debug(Debug_Trace t) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::trace>() << "[TRC]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::trace>();
}