#pragma once

#include "libgomp.h"

namespace MOGSLib { namespace Context {

struct OmpDelayTest : public LibGOMP<Traits::Id, Traits::Load> {};

}}