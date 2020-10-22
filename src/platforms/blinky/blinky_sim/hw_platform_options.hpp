#ifndef SIM_DEMO_PLATFORM_HW_PLATFORM_OPTIONS_HPP
#define SIM_DEMO_PLATFORM_HW_PLATFORM_OPTIONS_HPP

#include <driver/driver_registry.hpp>

// The FW demo platform uses a dynamic driver registry since we are running on the host machine
using PlatformDriverRegistry = embvm::DynamicDriverRegistry<std::mutex>;

#endif // SIM_DEMO_PLATFORM_HW_PLATFORM_OPTIONS_HPP
