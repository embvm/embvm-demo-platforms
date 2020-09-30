# meson build for fwdemo_simulator HW platform

# TODO: this should buidl as a library, not a dependency. Higher levels don't
# need (OR GET!) specific hardware access
blinky_simulator_hw_platform_dep = declare_dependency(
	include_directories: include_directories('.'),
	sources: [
		files('blinky_simulator_hw_platform.cpp')
	],
	dependencies: [
		aardvark_native_driver_dep,
		simulator_driver_dep,
		simulator_processor_dep,
		posix_os_dep
	]
)
