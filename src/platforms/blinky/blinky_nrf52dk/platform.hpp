// Copyright 2020 Embedded Artistry LLC
// SPDX-License-Identifier: MIT

#ifndef BLINKY_NRF52_DK_FWDEMO_PLATFORM_HPP_
#define BLINKY_NRF52_DK_FWDEMO_PLATFORM_HPP_

#include <blinky_platform.hpp>
#include <boot/boot_sequencer.hpp>
#include <nrf52dk_blinky_hw_platform.hpp>
#include <platform_options.hpp>

/// Firmware Demo Simulator Platform Declaration: Use Sim HW Platform
using VirtualPlatform = BlinkyDemoPlatform<NRF52DKHWPlatform>;
using PlatformBootSequencer = embvm::BootSequencer<embvm::DefaultBootStrategy<VirtualPlatform>>;

#endif // BLINKY_NRF52_PLATFORM_HPP_
