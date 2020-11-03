/*
 * Copyright © 2020 Embedded Artistry LLC.
 * See LICENSE file for licensing information.
 */

#include "platform.hpp"
#include <platform_logger.hpp>
#include <printf.h> // for _putchar definition
// TODO: test memory setup with linker scripts
//#include <malloc.h>

// extern int __HeapBase;
// extern int __HeapLimit;

void _putchar(char c)
{
	(void)c;
	// TODO: implement
}

// TODO: this is a temporary workaroudn for building fwdemo, because operator delete(void*) is being
// included, which wants free(). This might be another deleting destructor. Right now I just
// want to enable the build for a release to Ethan.
// A suitable solution for such cases may also be to include an asserting malloc/free, but
// I still want to know WHY this is being included.
void free(void* ptr)
{
	(void)ptr;
	assert(0); // Not supported - no dynamic memory here!
}

namespace
{
// TODO: FreeRTOS threaded support
// static constexpr size_t MAIN_THREAD_STACK_SIZE = 4096; // bytes
// static constexpr size_t LED_THREAD_STACK_SIZE = 2048;
// static embvm::VirtualThread* main_thread_ = nullptr;
} // namespace

void NucleoL4RZI_DemoPlatform::earlyInitHook_() noexcept
{
	// malloc_addblock(&__HeapBase, reinterpret_cast<uintptr_t>(&__HeapLimit) -
	//								 reinterpret_cast<uintptr_t>(&__HeapBase));

	NucleoL4R5ZI_HWPlatform::earlyInitHook();
}

void NucleoL4RZI_DemoPlatform::initOS_() noexcept
{
	// TODO: freertos threaded support
}

void NucleoL4RZI_DemoPlatform::initHWPlatform_() noexcept
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

void NucleoL4RZI_DemoPlatform::initProcessor_() noexcept
{
	hw_platform_.initProcessor();
}

void NucleoL4RZI_DemoPlatform::init_() noexcept {}

void NucleoL4RZI_DemoPlatform::startBlink() noexcept
{
	hw_platform_.startBlink();
}

void NucleoL4RZI_DemoPlatform::echoLogBufferToConsole() noexcept
{
	PlatformLogger::inst().dump();
}
