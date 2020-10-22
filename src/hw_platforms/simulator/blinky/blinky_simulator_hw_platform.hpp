#ifndef SIMULATOR_HW_PLATFORM_HPP_
#define SIMULATOR_HW_PLATFORM_HPP_

#include <aardvark/base.hpp>
#include <aardvark/gpio.hpp>
#include <driver/led.hpp>
#include <hw_platform/timer_manager.hpp>
#include <hw_platform/virtual_hw_platform.hpp>
#include <simulator/system_clock.hpp>
#include <simulator/timer.hpp>
#include <simulator_processor.hpp>

// clang-format off
#include <dispatch/interrupt_queue.hpp> // This has to be last b/c of an OS X include pollution
// clang-format on

class BlinkySimulatorHWPlatform : public embvm::VirtualHwPlatformBase<BlinkySimulatorHWPlatform>
{
	using PlatformBase = embvm::VirtualHwPlatformBase<BlinkySimulatorHWPlatform>;
	using TimerManager_t = embvm::TimerManager<0, std::mutex>;

  public:
	/// @brief Default constructor.
	BlinkySimulatorHWPlatform() noexcept;

	/// @brief Default destructor.
	~BlinkySimulatorHWPlatform() noexcept;

#pragma mark - Inherited Functions -

	static void earlyInitHook_() noexcept {}

	void init_() noexcept;

	void initProcessor_() noexcept
	{
		processor.init();
	}

	void soft_reset_() noexcept {}

	void hard_reset_() noexcept
	{
		// We can't perform a hard reset of our computer from the simulator app...
		soft_reset_();
	}

#pragma mark - Custom Functions -

	/** Allocate a software timer
	 *
	 * Allocates a software timer from the underlying timer manager. A handle is returned,
	 * which the user can use to configure the timer according to their wishes.
	 *
	 * @returns handle to a software timer object
	 */
	auto allocateTimer() noexcept
	{
		return tm_.allocate();
	}

	/// @brief Start the LED timer
	void startBlink() noexcept
	{
		timer1.start();
	}

  private:
  private:
	embutil::InterruptQueue<std::mutex> irq_bottom_half_;

	embdrv::SimulatorSystemClock sysclock;
	embdrv::aardvarkAdapter aardvark{embdrv::aardvarkMode::GpioI2C};
	embdrv::aardvarkGPIOOutput<5> gpio5{aardvark};
	embvm::led::gpioActiveHigh led0{gpio5};

	// Leave unconfigured during declaration, update in init
	embdrv::SimulatorTimer timer0;
	embdrv::SimulatorTimer timer1;

	TimerManager_t tm_{timer1};
	TimerManager_t::TimerHandle led_sw_timer_handle;

	SimulatorProcessor processor;
};

#endif // SIMULATOR_HW_PLATFORM_HPP_
