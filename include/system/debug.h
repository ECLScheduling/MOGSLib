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

/**
 * @brief Null debugging class responsible for disabling debug messages without breaking the code semantic.
 *
 * @details Calls to this debug's functions result in nothing when the compiler is properly set to optimize code.
 */
class No_Debug {
public:

  template<typename T>
  No_Debug& operator<< (const T &o) {
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
 * @brief An enum to indicate that the debug message is of type error.
 */
enum Debug_Error {error = 1};

/** 
 * @brief A debug function that prints an error message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::error)> debug(Debug_Error e) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::error>() << "[ERR]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::error>();
}

/** 
 * @brief An enum to indicate that the debug message is of type warning.
 */
enum Debug_Warning {warning = 2};

/** 
 * @brief A debug function that prints a warning message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::warning)> debug(Debug_Warning w) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::warning>() << "[WRN]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::warning>();
}

/** 
 * @brief An enum to indicate that the debug message is of type information.
 */
enum Debug_Info {info = 3};

/** 
 * @brief A debug function that prints an information message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::info)> debug(Debug_Info i) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::info>() << "[INF]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::info>();
}

/** 
 * @brief An enum to indicate that the debug message is of type trace.
 */
enum Debug_Trace {trace = 4};

/** 
 * @brief A debug function that prints a trace message.
 */
template<typename T>
inline Selected_Debug<(Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::trace)> debug(Debug_Trace t) {
  Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::trace>() << "[TRC]: ";
  return Selected_Debug<Traits<T>::debugged && Traits<Debugger>::enabled && Traits<Debugger>::trace>();
}