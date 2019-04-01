#pragma once

#include "openmp.h"

namespace MOGSLib { namespace Context {

struct OmpDelayTest : public OpenMP<Traits::Id, Traits::Load> {};

}}