#ifndef STM32_NUCLEOl4_FWDEMO_PLATFORM_LOGGER_HPP_
#define STM32_NUCLEOl4_FWDEMO_PLATFORM_LOGGER_HPP_

#include <logging/circular_buffer_logger.hpp>
#include <nop_lock/nop_lock.hpp>

using PlatformLogger =
	embvm::PlatformLogger_t<embvm::CircularLogBufferLogger<1 * 1024, embutil::nop_lock>>;

#endif
