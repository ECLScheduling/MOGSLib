#pragma once

#include <type_traits>
#include <interfaces/adaptor/extensions/withGenericStructure.h>

/**
 * @brief This abstract class stub defines the requirements of the BinLPT algorithm input adaptor.
 * @details In order to BinLPT to function it needs all the data contained in a default adaptor interface and another parameter k (The maximum number of chunks).
 * Any adaptor that aims to serve as a input to BinLPT strategy must implement this abstract stub.
 * @type InputAdaptor The type that will be tested by this structure.
 * @type UInt The unsigned integer type that the library is being compiled to use.
 */
template<typename InputAdaptor, typename UInt>
struct BinLPTAdaptorRequirements {

  static const bool value = std::is_base_of< WithGenericStructure<UInt>, InputAdaptor>::value;
};