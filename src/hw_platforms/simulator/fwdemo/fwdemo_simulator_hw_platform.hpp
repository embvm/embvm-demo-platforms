#ifndef SIMULATOR_HW_PLATFORM_HPP_
#define SIMULATOR_HW_PLATFORM_HPP_

#include <aardvark/base.hpp>
#include <aardvark/gpio.hpp>
#include <aardvark/i2c.hpp>
#include <aardvark/spi.hpp>
#include <driver/led.hpp>
#include <hw_platform/timer_manager.hpp>
#include <hw_platform/virtual_hw_platform.hpp>
#include <simulator/system_clock.hpp>
#include <simulator/timer.hpp>
#include <simulator_processor.hpp>
#include <ssd1306.hpp>
#include <vl53l1x.hpp>

// clang-format off
#include <dispatch/interrupt_queue.hpp> // This has to be last b/c of an OS X include pollution
// clang-format on

#define SPARKFUN_VL53L1X_ADDR 0x29
#define SPARKFUN_SSD1306_ADDR 0x3D

/** Framework Demo Simulator Hardware Platform
 *
 * This implements an OSX-based hardware platform which provides the functionality
 * needed for our framework demo.
 *
 * I2C support is provided using an aardvark adapter. Higher-level device drivers utilize the
 * Aardvark I2C interface, enabling them to work on a host machine.
 *
 * To the application layer, this hardware is just as good as embedded hardware!
 *
 * Our configuration sports:
 *	- A system clock (sysclock)
 *	- An i2c port (i2c0)
 *	- 1 GPIO output (gpio5)
 *	- 2 GPIO inputs (gpio4, gpio3)
 *	- An LED (led0), connected to gpio5
 *	- A VL53L1X embvm::tof::sensor sensor (connected to i2c0)
 *	- An SSD1306 OLED display (connected to i2c0)
 *	- Two timers (timer0, timer1)
 *
 * The hardware platform also provides a timer manager (using timer1), which provides any number
 *	of software timers to be derived from it.
 */
class FWDemoSimulatorHWPlatform : public embvm::VirtualHwPlatformBase<FWDemoSimulatorHWPlatform>
{
	using PlatformBase = embvm::VirtualHwPlatformBase<FWDemoSimulatorHWPlatform>;
	using TimerManager_t = embvm::TimerManager<0, std::mutex>;

  public:
	using TimerHandle_t = TimerManager_t::TimerHandle;

  public:
	/// @brief Default constructor.
	FWDemoSimulatorHWPlatform() noexcept;

	/// @brief Default destructor.
	~FWDemoSimulatorHWPlatform() noexcept;

#pragma mark - Inherited Functions -

	static void earlyInitHook_() noexcept {}
	void init_() noexcept;
	void initProcessor_() noexcept;
	void soft_reset_() noexcept {}
	void hard_reset_() noexcept;

#pragma mark - Custom Functions -

	/// @brief Start the LED timer
	void startLEDTimer() noexcept
	{
		timer0.start();
	}

	/** Allocate a software timer
	 *
	 * Allocates a software timer from the underlying timer manager. A handle is returned,
	 * which the user can use to configure the timer according to their wishes.
	 *
	 * @returns handle to a software timer object
	 */
	TimerHandle_t allocateTimer() noexcept
	{
		return tm_.allocate();
	}

	/** Get the tof0 Instance
	 *
	 * You don't always need find_driver() in the DriverRegistry. You can directly return a
	 * base-class reference from the hardware platform. This saves time from doing a lookup.
	 *
	 * It is important to return the base class, since that is how we keep our applications
	 * decoupled from the underlying hardware. Returning the actual ToF sensor class will
	 * enable coupling to the underlying harware.
	 *
	 * @returns a reference to the tof0 instance, as the base class type.
	 */
	embvm::tof::sensor& tof0_inst() noexcept
	{
		return tof0;
	}

	/** Get the led0 Instance
	 *
	 * You don't always need find_driver() in the DriverRegistry. You can directly return a
	 * base-class reference from the hardware platform. This saves time from doing a lookup.
	 *
	 * It is important to return the base class, since that is how we keep our applications
	 * decoupled from the underlying hardware. Returning the actual ToF sensor class will
	 * enable coupling to the underlying harware.
	 *
	 * @returns a reference to the led0 instance, as the base class type.
	 */
	embvm::led::base& led0_inst() noexcept
	{
		return led0;
	}

	/** Get the screen0 Instance
	 *
	 * You don't always need find_driver() in the DriverRegistry. You can directly return a
	 * base-class reference from the hardware platform. This saves time from doing a lookup.
	 *
	 * It is important to return the base class, since that is how we keep our applications
	 * decoupled from the underlying hardware. Returning the actual ToF sensor class will
	 * enable coupling to the underlying harware.
	 *
	 * @returns a reference to the screen0 instance, as the base class type.
	 */
	embvm::basicDisplay& screen0_inst() noexcept
	{
		return screen0;
	}

	/** @brief Sets the ToF mode based on GPIO input
	 *
	 * Reads the mode GPIO and updates the ToF mode based on the setting.
	 *
	 * @returns the ToF mode setting read from HW
	 */
	embvm::tof::mode readAndSetToFMode() noexcept;

  private:
	embutil::InterruptQueue<std::mutex> irq_bottom_half_{};
	embdrv::SimulatorSystemClock sysclock{};
	embdrv::aardvarkAdapter aardvark{embdrv::aardvarkMode::GpioI2C};
	embdrv::aardvarkI2CMaster i2c0{aardvark};
	embdrv::aardvarkGPIO gpio5{aardvark, 5, embvm::gpio::mode::output};
	embdrv::aardvarkGPIO gpio4{aardvark, 4, embvm::gpio::mode::input};
	embdrv::aardvarkGPIO gpio3{aardvark, 3, embvm::gpio::mode::input};
	embvm::led::gpioActiveHigh led0{gpio5};
	embdrv::vl53l1x tof0{i2c0, SPARKFUN_VL53L1X_ADDR};
	embdrv::ssd1306 screen0{i2c0, SPARKFUN_SSD1306_ADDR};

	// Leave unconfigured during declaration, update in init
	embdrv::SimulatorTimer timer0{};

	TimerManager_t tm_{timer0};
	TimerHandle_t led_sw_timer_handle{};

	SimulatorProcessor processor;
};

#endif // SIMULATOR_HW_PLATFORM_HPP_
