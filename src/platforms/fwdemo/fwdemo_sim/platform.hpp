#ifndef FWDEMO_SIMULATOR_PLATFORM_HPP_
#define FWDEMO_SIMULATOR_PLATFORM_HPP_

#include <boot/boot_sequencer.hpp>
#include <driver/system_clock.hpp>
#include <driver/time_of_flight.hpp>
#include <fwdemo_simulator_hw_platform.hpp>
#include <platform/virtual_platform.hpp>
#include <platform_logger.hpp>
#include <platform_options.hpp>

/// Signal variable to exit the main() loop
/// Declared in main.c, set in Sim Platform's boot.cpp using std::signal
extern volatile bool abort_program_;

class FrameworkDemoSimPlatform
	: public embvm::VirtualPlatformBase<FrameworkDemoSimPlatform, FWDemoSimulatorHWPlatform>
{
	using VirtualPlatform =
		embvm::VirtualPlatformBase<FrameworkDemoSimPlatform, FWDemoSimulatorHWPlatform>;

  public:
#pragma mark - Base Platform Functions
	static void earlyInitHook_() noexcept {}
	void init_() noexcept;
	void initProcessor_() noexcept;
	void initHWPlatform_() noexcept;

#pragma mark - FWDemo Platform Functions -

	void startBlink() noexcept;
	void echoLogBufferToConsole() noexcept;

	// TODO: can I make these private somehow? I dont' want people creating their own simulator
	// platforms except through the factory
  public:
	/// Default constructor
	FrameworkDemoSimPlatform() noexcept {}

	~FrameworkDemoSimPlatform() = default;

  private:
	void updateToFMode() noexcept;

  private:
	FWDemoSimulatorHWPlatform::TimerHandle_t led_sw_timer_handle{};
};

using VirtualPlatform = FrameworkDemoSimPlatform;
using PlatformBootSequencer = embvm::BootSequencer<OSXSimulatorBootStrategy<VirtualPlatform>>;

#endif // FWDEMO_SIMULATOR_PLATFORM_HPP_
