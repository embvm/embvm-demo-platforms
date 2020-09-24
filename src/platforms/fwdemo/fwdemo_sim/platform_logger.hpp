#ifndef FWDEMO_SIM_PLATFORM_LOGGER_HPP_
#define FWDEMO_SIM_PLATFORM_LOGGER_HPP_

#include <logging/circular_buffer_logger.hpp>
#include <mutex>

using PlatformLogger =
	embvm::PlatformLogger_t<embvm::CircularLogBufferLogger<8 * 1024, std::mutex>>;

#endif // FWDEMO_SIM_PLATFORM_LOGGER_HPP_
