#pragma once

#include <system/static.h>
#include <strategies/adaptor/interface/defaultAdaptorRequirements.h>
#include <strategies/adaptor/interface/extensions/withGenericStructure.h>


HAS_TYPE_MACRO(UInt, has_uint_definition)

/**
 * This abstract class stub defines the requirements of the BinLPT algorithm input adaptor.
 * @details In order to BinLPT to function it needs all the data contained in a default adaptor interface and another parameter k (The maximum number of chunks).
 * Any adaptor that aims to serve as a input to BinLPT strategy must implement this abstract stub.
 */
template<typename InputAdaptor>
struct BinLPTAdaptorRequirements {
  static_assert(DefaultAdaptorRequirements<InputAdaptor>::value, "InputAdaptor structure passed to BinLPTAdaptor does not meet the static requirements.");

  static const bool value = std::is_base_of< WithGenericStructure<typename InputAdaptor::UInt>, InputAdaptor>::value;
};