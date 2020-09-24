#ifndef SIM_BLINKY_PLATFORM_OPTIONS_HPP_
#define SIM_BLINKY_PLATFORM_OPTIONS_HPP_

#include <platform/virtual_platform.hpp>

// The FW demo platform uses a dynamic driver registry since we are running on the host machine
using PlatformDriverRegistry = embvm::DynamicDriverRegistry<std::mutex>;

#endif
