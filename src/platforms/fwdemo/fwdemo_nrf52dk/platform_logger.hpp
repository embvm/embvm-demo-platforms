#ifndef NRF52_DK_BLINKY_PLATFORM_LOGGER_HPP_
#define NRF52_DK_BLINKY_PLATFORM_LOGGER_HPP_

#include <logging/circular_buffer_logger.hpp>
#include <mutex>

using PlatformLogger =
	embvm::PlatformLogger_t<embvm::CircularLogBufferLogger<4 * 1024, std::mutex>>;

#endif
