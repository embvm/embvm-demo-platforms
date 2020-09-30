#include "nrf52dk_blinky_hw_platform.hpp"
#include <cassert>

NRF52DKHWPlatform::~NRF52DKHWPlatform() noexcept {}

void NRF52DKHWPlatform::earlyInitHook_() noexcept {}

void NRF52DKHWPlatform::init_() noexcept
{
	// start all LEDs
	// turn them off? Or just trust that they start off?
	led1.start();
	led2.start();
	led3.start();
	led4.start();
}

void NRF52DKHWPlatform::startBlink() noexcept
{
	while(true)
	{
		for(const auto& led : {&led1, &led2, &led3, &led4})
		{
			led->toggle();
			processor.spin(500 * 1000); // 500ms
		}
	}
}

void NRF52DKHWPlatform::leds_off() noexcept
{
	led1.off();
	led2.off();
	led2.off();
	led2.off();
}

void NRF52DKHWPlatform::hard_reset_() noexcept
{
	// We can't perform a hard reset of our computer from the simulator app...
	soft_reset_();
}

void NRF52DKHWPlatform::initProcessor_() noexcept {}
void NRF52DKHWPlatform::soft_reset_() noexcept {}
