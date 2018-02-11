#pragma once

#include <iostream>
#include <system/traits.h>

/**
 * @brief Debugging class responsible for outputting debug messages.
 */
class Debug {
public:
  
  template<typename T>
  Debug& operator<< (const T &p) {
    std::cout << p;
    return *this;
  }
};

#define UNUSED(x) (void)(x)
/**
 * @brief Null debugging class responsible for disabling debug messages without breaking the code semantic.
 *
 * @details Calls to this debug's functions result in nothing when the compiler is properly set to optimize code.
 */
class No_Debug {
public:

  template<typename T>
  No_Debug& operator<< (const T &o) {
    UNUSED(o);
    return *this;
  }
};

/** 
 * @brief A proxy class to unify the semantic of No_Debug and Debug through a static boolean in compilation time.
 */
template<bool debugging>
class Selected_Debug : public Debug {};

/** 
 * @brief A proxy class to unify the semantic of No_Debug and Debug through a static boolean in compilation time.
 */
template<>
class Selected_Debug<false> : public No_Debug {};


/** 
 * @brief A debug function that prints an error message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::error)> debug_err() {
  Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::error>() << "[ERR]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::error>();
}

/** 
 * @brief A debug function that prints a warning message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::warning)> debug_wrn() {
  Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::warning>() << "[WRN]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::warning>();
}

/** 
 * @brief A debug function that prints an information message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::info)> debug_inf() {
  Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::info>() << "[INF]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::info>();
}

/** 
 * @brief A debug function that prints a trace message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::trace)> debug_trc() {
  Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::trace>() << "[TRC]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<LibDebugger>::enabled && Traits<LibDebugger>::trace>();
}