// Copyright 2020 Embedded Artistry LLC
// SPDX-License-Identifier: MIT

#ifndef NUCLEO_L4R5ZI_HW_PLATFORM_HPP_
#define NUCLEO_L4R5ZI_HW_PLATFORM_HPP_

#include <driver/led.hpp>
#include <hw_platform/virtual_hw_platform.hpp>
#include <ssd1306.hpp>
#include <stm32_dma.hpp>
#include <stm32_gpio.hpp>
#include <stm32_i2c_master.hpp>
#include <stm32_timer.hpp>
#include <stm32l4r5.hpp>
#include <vl53l1x.hpp>

#define SPARKFUN_VL53L1X_ADDR 0x29
#define SPARKFUN_SSD1306_ADDR 0x3D

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

	embvm::tof::sensor& tof0_inst() noexcept
	{
		return tof0;
	}

	embvm::basicDisplay& screen0_inst() noexcept
	{
		return screen0;
	}

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

	STM32DMA dma_ch_i2c_tx{STM32DMA::device::dma1, STM32DMA::channel::CH1};
	STM32DMA dma_ch_i2c_rx{STM32DMA::device::dma1, STM32DMA::channel::CH2};
	STM32I2CMaster i2c2{STM32I2CMaster::device::i2c2, dma_ch_i2c_tx, dma_ch_i2c_rx};
	embdrv::ssd1306 screen0{i2c2, SPARKFUN_SSD1306_ADDR};
	embdrv::vl53l1x tof0{i2c2, SPARKFUN_VL53L1X_ADDR};
};

#endif // NUCLEO_L4R5ZI_HW_PLATFORM_HPP_
