#pragma once

namespace Concepts {

/**
 * @brief A class that serves the purpose of represening the absence of application data for the scheduler at compile time.
 */
struct NoApplicationData {};

/**
 * @brief A class that serves the purpose of represening the absence of application's task data at compile time.
 */
struct NoTaskData {};

/**
 * @brief A class that declares the conceptual application data.
 * @type TaskData The type that wraps the application's task data.
 */
template<typename TaskData = NoTaskData>
struct ApplicationData {
  TaskData tasks;
};

template<>
struct ApplicationData<NoTaskData> {};

}