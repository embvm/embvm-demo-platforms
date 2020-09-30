#include "blinky_simulator_hw_platform.hpp"
#include <cassert>
#include <logging/log.hpp>

BlinkySimulatorHWPlatform::~BlinkySimulatorHWPlatform() noexcept {}

void BlinkySimulatorHWPlatform::init_() noexcept
{
	led0.start();

	// TimerManager timer needs an IRQ queue
	timer1.setBottomHalfDispatcher(irq_bottom_half_.getBoundDispatch());

	led_sw_timer_handle = allocateTimer();
	led_sw_timer_handle.periodicDelay(std::chrono::milliseconds(500),
									  [&]() noexcept { led0.toggle(); });
}
