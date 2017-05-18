#pragma once

#include <string>

/**
 * This namespace serve as a centralized point of definition for verbal error messages.
 */
namespace Error {
  const std::string MIGRATION_OUT_OF_BOUNDS = "Migrations array tried to be accessed out of bounds.";

  const std::string INPUT_OUT_OF_BOUNDS = "Input data array tried to be accessed out of bounds.";
}

