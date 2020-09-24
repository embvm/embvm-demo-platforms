# meson build for fwdemo_simulator HW platform

fwdemo_simulator_hw_platform_dep = declare_dependency(
	include_directories: include_directories('.'),
	sources: [files('fwdemo_simulator_hw_platform.cpp')],
	dependencies: [aardvark_driver_dep,
		st_vl53l1x_driver_dep,
		ssd1305_dep,
		simulator_driver_dep,
		simulator_processor_dep,
	]
)
