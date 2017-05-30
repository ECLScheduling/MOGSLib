#pragma once

#include <string>

/**
 * This namespace serve as a centralized point of definition for verbal error messages.
 */
namespace Error {
  const std::string MIGRATION_INVALID_TASK = "Tried to access a Task mapped for migration with an invalid identifier.";

  const std::string INVALID_INPUT_ACCESS = "Tried to access an input with an invalid identified.";
}