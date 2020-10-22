#ifndef FW_DEMO_SIM_HW_PLATFORM_OPTIONS_HPP_
#define FW_DEMO_SIM_HW_PLATFORM_OPTIONS_HPP_

#include <mutex>
#include <platform/virtual_platform.hpp>

// The FW demo platform uses a dynamic driver registry since we are running on the host machine
using PlatformDriverRegistry = embvm::DynamicDriverRegistry<std::mutex>;

#endif // FW_DEMO_SIM_HW_PLATFORM_OPTIONS_HPP_
