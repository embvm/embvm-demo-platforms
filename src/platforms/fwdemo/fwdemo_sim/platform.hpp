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

/// This Platform serves as a base class that the specific framework demo applications
/// Can derive from. This class takes a hardware platform as a template.
/// Clients should implement specific instances of this platform as follows:
///
/// @code
/// using VirtualPlatform = embvm::VirtualPlatformBase<
///		FrameworkDemoPlatform<SimulatorHWPlatform>, PlatformDriverRegistry>;
/// @endcode
class FrameworkDemoSimPlatform
	: public embvm::VirtualPlatformBase<FrameworkDemoSimPlatform, PlatformDriverRegistry>
{
	using VirtualPlatform =
		embvm::VirtualPlatformBase<FrameworkDemoSimPlatform, PlatformDriverRegistry>;

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

	/// Child classes can override the simulator platform name using the std::string_view
	/// constructor
	explicit FrameworkDemoSimPlatform(const std::string_view& name) noexcept : VirtualPlatform(name)
	{
	}

	~FrameworkDemoSimPlatform() = default;

  private:
	void updateToFMode() noexcept;

  private:
	FWDemoSimulatorHWPlatform hw_platform_{};

	FWDemoSimulatorHWPlatform::TimerHandle_t led_sw_timer_handle{};
};

using VirtualPlatform = FrameworkDemoSimPlatform;
using PlatformBootSequencer = embvm::BootSequencer<OSXSimulatorBootStrategy<VirtualPlatform>>;

#endif // FWDEMO_SIMULATOR_PLATFORM_HPP_
