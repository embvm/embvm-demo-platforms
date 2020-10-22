#ifndef BLINKY_NRF52_DONGLE_PLATFORM_HPP_
#define BLINKY_NRF52_DONGLE_PLATFORM_HPP_

#include <blinky_platform.hpp>
#include <boot/boot_sequencer.hpp>
#include <nrf52_dongle_hw_platform.hpp>
#include <platform_options.hpp>

/// Firmware Demo Simulator Platform Declaration: Use Sim HW Platform
using VirtualPlatform = BlinkyDemoPlatform<NRF52DongleHWPlatform>;
using PlatformBootSequencer = embvm::BootSequencer<embvm::DefaultBootStrategy<VirtualPlatform>>;

#endif // BLINKY_NRF52_PLATFORM_HPP_
