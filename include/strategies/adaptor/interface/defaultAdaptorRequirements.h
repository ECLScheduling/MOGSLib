#pragma once

#include <system/static.h>

HAS_TYPE_MACRO(Load, has_load_type)
HAS_TYPE_MACRO(Id, has_id_type)
HAS_TYPE_MACRO(UInt, has_uint_type)

template<typename AdaptorType>
struct DefaultAdaptorRequirements {

  static_assert(has_uint_type<AdaptorType>::value, "Error: InputAdaptor must define an UInt typename as an unsigned integral type.");
  static_assert(has_load_type<AdaptorType>::value, "Error: InputAdaptor must define a Load typename as a Task/PE load type.");
  static_assert(has_id_type<AdaptorType>::value, "Error: InputAdaptor must define an Id typename as a form to identify Tasks/PEs in target RTS.");
  
  const static bool value = has_uint_type<AdaptorType>::value && has_load_type<AdaptorType>::value && has_id_type<AdaptorType>::value;
};