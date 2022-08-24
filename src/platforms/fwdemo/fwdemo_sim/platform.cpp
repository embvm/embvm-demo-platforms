#include "platform.hpp"

namespace
{
char tof_string_[32];
char tof_mode_string_[32];
} // namespace

void FrameworkDemoSimPlatform::init_() noexcept
{
	auto clk = VirtualPlatform::template findDriver<embvm::clk::SystemClock>();
	if(clk)
	{
		PlatformLogger::inst().setClock(*clk.value());
	}

	// Instead of using find_driver(), we will get the instance directly
	// from the hardware platform. We use auto& because we are receiving
	// a reference to the base class.
	auto& tof = hw_platform_.tof0_inst();
	tof.registerReadCallback([](uint16_t v) { printf("ToF Range: %u mm\n", v); });
}

void FrameworkDemoSimPlatform::initProcessor_() noexcept
{
	hw_platform_.initProcessor();
}

void FrameworkDemoSimPlatform::initHWPlatform_() noexcept
{
	hw_platform_.init();

	auto& tof0 = hw_platform_.tof0_inst();
	auto& screen0 = hw_platform_.screen0_inst();

	tof0.start();
	tof0.registerReadCallback([&](uint16_t v) {
		snprintf(tof_string_, 32, "ToF Range: %u mm\n", v);
		screen0.clear();
		screen0.printString(0, 0, tof_string_);
		screen0.printString(0, 32, tof_mode_string_);
		screen0.display();
	});

	updateToFMode();
}

void FrameworkDemoSimPlatform::startBlink() noexcept
{
	led_sw_timer_handle = hw_platform_.allocateTimer();
	auto& led0 = hw_platform_.led0_inst();

	led_sw_timer_handle.periodicDelay(std::chrono::milliseconds(500),
									  [&]() noexcept { led0.toggle(); });
	hw_platform_.startLEDTimer();
}

void FrameworkDemoSimPlatform::echoLogBufferToConsole() noexcept
{
	PlatformLogger::inst().dump();
}

void FrameworkDemoSimPlatform::updateToFMode() noexcept
{
	const char* mode_string = nullptr;
	auto m = hw_platform_.readAndSetToFMode();
	switch(m)
	{
		case embvm::tof::mode::defaultRange:
			mode_string = "deflt";
			break;
		case embvm::tof::mode::shortRange:
			mode_string = "short";
			break;
		case embvm::tof::mode::medRange:
			mode_string = "med";
			break;
		case embvm::tof::mode::longRange:
			mode_string = "long";
			break;
		default:
			mode_string = "invld";
			break;
	}

	snprintf(tof_mode_string_, 32, "M: %s", mode_string);
}
