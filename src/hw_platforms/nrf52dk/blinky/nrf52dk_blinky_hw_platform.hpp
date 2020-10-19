#ifndef NRF52_DK_HW_PLATFORM_HPP_
#define NRF52_DK_HW_PLATFORM_HPP_

#include <driver/led.hpp>
#include <hw_platform/virtual_hw_platform.hpp>
#include <nRF52840.hpp>
#include <nrf_gpio.hpp>

#define SPARKFUN_VL53L1X_ADDR 0x29
#define SPARKFUN_SSD1306_ADDR 0x3D

class NRF52DKHWPlatform : public embvm::VirtualHwPlatformBase<NRF52DKHWPlatform>
{
	using PlatformBase = embvm::VirtualHwPlatformBase<NRF52DKHWPlatform>;

  public:
	/// @brief Default constructor.
	NRF52DKHWPlatform() noexcept : PlatformBase("nRF52840 Development Kit") {}

	/// @brief Default destructor.
	~NRF52DKHWPlatform() noexcept;

#pragma mark - Inherited Functions -

	static void earlyInitHook_() noexcept;
	void init_() noexcept;
	void initProcessor_() noexcept;
	void soft_reset_() noexcept;
	void hard_reset_() noexcept;

#pragma mark - Custom Functions -

	void leds_off() noexcept;
	void startBlink() noexcept;

  private:
	nRF52840 processor;

	nRFGPIOOutput<0, 13> led1_pin{};
	nRFGPIOOutput<0, 14> led2_pin{};
	nRFGPIOOutput<0, 15> led3_pin{};
	nRFGPIOOutput<0, 16> led4_pin{};

	embvm::led::gpioActiveLow led1{led1_pin, "led1"};
	embvm::led::gpioActiveLow led2{led2_pin, "led2"};
	embvm::led::gpioActiveLow led3{led3_pin, "led3"};
	embvm::led::gpioActiveLow led4{led4_pin, "led4"};
};

#endif // NRF52_DK_HW_PLATFORM_HPP_
