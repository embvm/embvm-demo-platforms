# Simulator variant of the FW Demo Platform

blinky_nrf52dongle_platform_inc = include_directories('.')

blinky_nrf52dongle_platform_dep = declare_dependency(
	include_directories: blinky_nrf52dongle_platform_inc,
	sources: [
		files('platform.cpp')
	],
	dependencies: [
		nrf52840_dongle_hw_platform_dep,
		blinky_demo_platform_dep,
		framework_threadless_dep
	],
	link_args: [
		'-L' + meson.current_source_dir(),
		'-Tblinky_gcc_nrf52.ld',
	],
	sources: files('platform.cpp'),
)

# Compilation target for CI purposes
if(meson.is_subproject() == false)
	blinky_nrf52dongle_platform = static_library('blinky_nrf52dongle_platform',
		dependencies: blinky_nrf52dongle_platform_dep,
	)
endif
