#ifndef FWDEMO_NRF52_DK_PLATFORM_HPP_
#define FWDEMO_NRF52_DK_PLATFORM_HPP_

#include <boot/boot_sequencer.hpp>
#include <nrf52dk_fwdemo_hw_platform.hpp>
#include <os.hpp>
#include <platform/virtual_platform.hpp>
#include <platform_logger.hpp>
#include <platform_options.hpp>

/// Signal variable to exit the main() loop
/// Declared in main.c, set in Sim Platform's boot.cpp using std::signal
extern volatile bool abort_program_;

class nRF52DK_FrameworkDemoPlatform final
	: public embvm::VirtualPlatformBase<nRF52DK_FrameworkDemoPlatform, NRF52DKHWPlatform>
{
	using PlatformBase =
		embvm::VirtualPlatformBase<nRF52DK_FrameworkDemoPlatform, NRF52DKHWPlatform>;

  public:
#pragma mark - Base Platform Functions

	static void earlyInitHook_() noexcept;
	static void initOS_(void (*main_thread)()) noexcept;
	void init_() noexcept;
	void initProcessor_() noexcept;
	void initHWPlatform_() noexcept;

#pragma mark - FWDemo Platform Functions -

	void startBlink() noexcept;
	void echoLogBufferToConsole() noexcept;

#pragma mark - Custom Platform Functions -

  public:
	/// Default constructor
	nRF52DK_FrameworkDemoPlatform() noexcept {}
	~nRF52DK_FrameworkDemoPlatform() = default;

  private:
	void led_blink_thread_() noexcept;

#pragma mark - Data Members -
  private:
	/** Thread handle for the created-during-runtime LED thread
	 *
	 * We defer initialization of the LED thread so that we can can start the blinking process
	 * at a time of our choosing, rather than during the construction process.
	 *
	 * This is just one approach at handling startBlink() for this platform. Another approach
	 * would be to create the thread statically and use a variable to wake the thread when
	 * we are ready for blinking to start.
	 */
	embvm::VirtualThread* led_thread_ = nullptr;
};

using VirtualPlatform = nRF52DK_FrameworkDemoPlatform;
using PlatformBootSequencer =
	embvm::BootSequencer<embvm::BootOSWithMainThreadStrategy<VirtualPlatform>>;

#endif // BLINKY_NRF52_PLATFORM_HPP_
