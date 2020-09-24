#ifndef NRF52_DK_BLINKY_PLATFORM_OPTIONS_HPP_
#define NRF52_DK_BLINKY_PLATFORM_OPTIONS_HPP_

#include <platform/virtual_platform.hpp>

// The FW demo platform uses a dynamic driver registry since we are running on the host machine
using PlatformDriverRegistry = embvm::StaticDriverRegistry<12>;

#endif
