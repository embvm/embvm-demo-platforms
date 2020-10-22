#ifndef BLINKY_SIMULATOR_PLATFORM_HPP_
#define BLINKY_SIMULATOR_PLATFORM_HPP_

#include <blinky_platform.hpp>
#include <blinky_simulator_hw_platform.hpp>
#include <boot/boot_sequencer.hpp>
#include <platform_options.hpp>

/// Firmware Demo Simulator Platform Declaration: Use Sim HW Platform
using VirtualPlatform = BlinkyDemoPlatform<BlinkySimulatorHWPlatform>;
using PlatformBootSequencer = embvm::BootSequencer<OSXSimulatorBootStrategy<VirtualPlatform>>;

#endif // BLINKY_SIMULATOR_PLATFORM_HPP_
