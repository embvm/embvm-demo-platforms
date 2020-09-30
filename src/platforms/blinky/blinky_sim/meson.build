# Simulator variant of the FW Demo Platform

blinky_sim_platform_inc = include_directories('.')

blinky_sim_platform_dep = declare_dependency(
	include_directories: blinky_sim_platform_inc,
	dependencies: [
		blinky_simulator_hw_platform_dep,
		blinky_demo_platform_dep,
		framework_native_dep
	],
	sources: files('platform.cpp'),
)

# This is used for running framework components on the host machine when cross compilation is used
if host_machine.cpu_family() == 'x86_64'
	blinky_sim_x86_platform_dep = declare_dependency(
		include_directories: blinky_sim_platform_inc,
		dependencies: [
			blinky_simulator_hw_platform_dep,
			blinky_demo_platform_dep,
			framework_dep
		],
		sources: files('platform.cpp'),
	)
endif
