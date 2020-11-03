#ifndef NUCLEO_L4R5ZI_HW_PLATFORM_HPP_
#define NUCLEO_L4R5ZI_HW_PLATFORM_HPP_

#include <driver/led.hpp>
#include <hw_platform/virtual_hw_platform.hpp>
#include <stm32_gpio.hpp>
#include <stm32_timer.hpp>
#include <stm32l4r5.hpp>

class NucleoL4R5ZI_HWPlatform : public embvm::VirtualHwPlatformBase<NucleoL4R5ZI_HWPlatform>
{
	using HWPlatformBase = embvm::VirtualHwPlatformBase<NucleoL4R5ZI_HWPlatform>;

  public:
	/// @brief Default constructor.
	NucleoL4R5ZI_HWPlatform() noexcept;

	/// @brief Default destructor.
	~NucleoL4R5ZI_HWPlatform() noexcept;

	// Required functions
	static void earlyInitHook_() noexcept;
	void init_() noexcept;
	void initProcessor_() noexcept;
	void soft_reset_() noexcept;
	void hard_reset_() noexcept;

	// Public APIs
	void leds_off() noexcept;
	void startBlink() noexcept;

  private:
	// TODO: maybe all of this can be hidden in the .cpp file, meaning we dont' need to
	// Expose any dependnecies or non-portable headers here!!!!
	stm32l4r5 processor_;

	STM32GPIO<embvm::gpio::port::C, 7> led1_pin{embvm::gpio::mode::output};
	STM32GPIO<embvm::gpio::port::B, 7> led2_pin{embvm::gpio::mode::output};
	STM32GPIO<embvm::gpio::port::B, 14> led3_pin{embvm::gpio::mode::output};

	embvm::led::gpioActiveHigh led1{led1_pin};
	embvm::led::gpioActiveHigh led2{led2_pin};
	embvm::led::gpioActiveHigh led3{led3_pin};

	// TODO: this isn't actually quite 1s right now...
	STM32Timer timer0{embvm::timer::channel::CH2, std::chrono::seconds(1)};
};

#endif // NUCLEO_L4R5ZI_HW_PLATFORM_HPP_
