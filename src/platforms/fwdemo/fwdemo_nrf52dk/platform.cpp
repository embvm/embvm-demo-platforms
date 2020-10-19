#include "platform.hpp"
#include <bounce/bounce.hpp>
#include <cassert>
#include <logging/log.hpp>
#include <malloc.h>

extern int __HeapBase;
extern int __HeapLimit;

namespace
{
static constexpr size_t MAIN_THREAD_STACK_SIZE = 4096; // bytes
static constexpr size_t LED_THREAD_STACK_SIZE = 2048;

static embvm::VirtualThread* main_thread_ = nullptr;

char tof_string_[32];
char tof_mode_string_[32];
} // namespace

void nRF52DK_FrameworkDemoPlatform::earlyInitHook_() noexcept
{
	malloc_addblock(&__HeapBase, reinterpret_cast<uintptr_t>(&__HeapLimit) -
									 reinterpret_cast<uintptr_t>(&__HeapBase));
	// TODO: need to forward to hardware platform early init hook? or does the boot code take care
	// of that?
}

void nRF52DK_FrameworkDemoPlatform::initOS_(void (*main_thread_func)()) noexcept
{
	// TODO: move this into the startScheduler call, use CAS, and make the freertos OS responsible.
	main_thread_ = os::Factory::createThread(
		"Main Thread", reinterpret_cast<embvm::thread::func_t>(main_thread_func), nullptr,
		embvm::thread::priority::normal, MAIN_THREAD_STACK_SIZE);
	os::freertos::startScheduler();
}

void nRF52DK_FrameworkDemoPlatform::initHWPlatform_() noexcept
{
	hw_platform_.init();

	auto& tof0 = hw_platform_.tof0_inst();
	auto& screen0 = hw_platform_.screen0_inst();

	tof0.registerReadCallback([&](uint16_t v) {
		snprintf(tof_string_, 32, "ToF Range: %u mm\n", v);
		screen0.clear();
		screen0.printString(0, 0, tof_string_);
		screen0.printString(0, 32, tof_mode_string_);
		screen0.display();
	});
}

void nRF52DK_FrameworkDemoPlatform::initProcessor_() noexcept
{
	hw_platform_.initProcessor();
}

void nRF52DK_FrameworkDemoPlatform::init_() noexcept
{
	auto clk = VirtualPlatform::template findDriver<embvm::clk::SystemClock>();
	if(clk)
	{
		PlatformLogger::inst().setClock(clk.value());
	}
	else
	{
		logdebug("No system clock instance found. Proceeding without timestamps.\n");
	}
}

void nRF52DK_FrameworkDemoPlatform::startBlink() noexcept
{
	if(!led_thread_)
	{
		led_thread_ =
			os::Factory::createThread("led thread",
									  reinterpret_cast<embvm::thread::func_t>(
										  BOUNCE(nRF52DK_FrameworkDemoPlatform, led_blink_thread_)),
									  reinterpret_cast<embvm::thread::input_t>(this),
									  embvm::thread::priority::low, LED_THREAD_STACK_SIZE);
		assert(led_thread_);
	}
}

void nRF52DK_FrameworkDemoPlatform::echoLogBufferToConsole() noexcept
{
	PlatformLogger::inst().dump();
}

void nRF52DK_FrameworkDemoPlatform::led_blink_thread_() noexcept
{
	static const auto led_list = hw_platform_.getLEDInstances();
	static const auto delay = std::chrono::milliseconds(500);

	while(1)
	{
		for(const auto& led : led_list)
		{
			led->toggle();
			embvm::this_thread::sleep_for(delay);
		}
	}
}
