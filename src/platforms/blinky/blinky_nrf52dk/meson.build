# Simulator variant of the FW Demo Platform

blinky_nrf52dk_platform_inc = include_directories('.')

blinky_nrf52dk_platform_dep = declare_dependency(
	include_directories: blinky_nrf52dk_platform_inc,
	sources: [
		files('platform.cpp')
	],
	dependencies: [
		nf52dk_blinky_hw_platform_dep,
		blinky_demo_platform_dep,
		framework_threadless_dep
	],
	link_args: [
		'-L' + meson.current_source_dir(),
		'-Tblinky_gcc_nrf52.ld',
	],
)

# Compilation target for CI purposes
if(meson.is_subproject() == false)
	blinky_nrf52dk_platform = static_library('blinky_nrf52dk_platform',
		dependencies: blinky_nrf52dk_platform_dep,
	)
endif
