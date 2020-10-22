#include "fwdemo_simulator_hw_platform.hpp"
#include <cassert>
#include <logging/log.hpp>

FWDemoSimulatorHWPlatform::FWDemoSimulatorHWPlatform() noexcept
{
	registerDriver("sysclock", &sysclock);
	registerDriver("gpio4", &gpio4);
	registerDriver("gpio3", &gpio3);
	// Note that led0 is registered, but not gpio5
	registerDriver("led0", &led0);
	registerDriver("i2c0", &i2c0);
	registerDriver("tof0", &tof0);
	registerDriver("screen0", &screen0);
}

FWDemoSimulatorHWPlatform::~FWDemoSimulatorHWPlatform() noexcept
{
	/// Turn off the screen & led before exiting the program
	screen0.stop();
}

void FWDemoSimulatorHWPlatform::hard_reset_() noexcept
{
	// We can't perform a hard reset of our computer from the simulator app...
	soft_reset_();
}

void FWDemoSimulatorHWPlatform::initProcessor_() noexcept
{
	processor.init();
}

void FWDemoSimulatorHWPlatform::init_() noexcept
{
	timer0.setBottomHalfDispatcher(irq_bottom_half_.getBoundDispatch());

	i2c0.start();
	i2c0.configure(embvm::i2c::baud::standard, embvm::i2c::pullups::external);

	led0.start();

	gpio3.start();
	gpio4.start();

	screen0.start();
}

embvm::tof::mode FWDemoSimulatorHWPlatform::readAndSetToFMode() noexcept
{
	uint8_t bit0 = static_cast<uint8_t>(gpio3.get());
	uint8_t bit1 = static_cast<uint8_t>(gpio4.get());

	logdebug("Switch setting on boot: bit0: %d, bit1: %d\n", bit0, bit1);

	embvm::tof::mode m = static_cast<embvm::tof::mode>(((bit1 << 1) | (bit0)));

	tof0.mode(m);

	return m;
}
