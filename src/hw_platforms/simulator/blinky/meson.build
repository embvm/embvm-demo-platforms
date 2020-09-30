# meson build for fwdemo_simulator HW platform

blinky_simulator_hw_platform_dep = declare_dependency(
	include_directories: include_directories('.'),
	sources: [files('blinky_simulator_hw_platform.cpp')],
	dependencies: [aardvark_driver_dep,
		simulator_driver_dep,
		simulator_processor_dep,
		posix_os_dep
	]
)
