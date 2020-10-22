#ifndef BLINKY_BASE_PLATFORM_HPP_
#define BLINKY_BASE_PLATFORM_HPP_

#include <driver/system_clock.hpp>
#include <platform/virtual_platform.hpp>
#include <platform_logger.hpp>

/// Signal variable to exit the main() loop
/// Declared in main.c, set in Sim Platform's boot.cpp using std::signal
extern volatile bool abort_program_;

/// This Platform serves as a base class that the specific framework demo applications
/// Can derive from. This class takes a hardware platform as a template.
/// Clients should implement specific instances of this platform as follows:
///
/// @code
/// using VirtualPlatform = embvm::VirtualPlatformBase<
///		BlinkyDemoPlatform<SimulatorHWPlatform>, PlatformDriverRegistry>;
/// @endcode
template<class THWPlatform, class TDriverRegistry>
class BlinkyDemoPlatform
	: public embvm::VirtualPlatformBase<BlinkyDemoPlatform<THWPlatform, TDriverRegistry>,
										TDriverRegistry>
{
	using VirtualPlatform =
		embvm::VirtualPlatformBase<BlinkyDemoPlatform<THWPlatform, TDriverRegistry>,
								   TDriverRegistry>;

  public:
	static void earlyInitHook_() noexcept
	{
		THWPlatform::earlyInitHook();
	}

	static void initOS_() noexcept {}

	void init_() noexcept {}

	void initProcessor_() noexcept
	{
		hw_platform_.initProcessor();
	}

	void initHWPlatform_() noexcept
	{
		hw_platform_.init();
	}

	void startBlink() noexcept
	{
		hw_platform_.startBlink();
	}

	// TODO: can I make these private somehow? I dont' want people creating their own simulator
	// platforms except through the factory
  public:
	/// Default constructor supplies a default name for the simulator platform
	BlinkyDemoPlatform() noexcept
	{
		// empty
	}

	~BlinkyDemoPlatform() = default;

  private:
	THWPlatform hw_platform_;
};

#endif // BLINKY_BASE_PLATFORM_HPP_
