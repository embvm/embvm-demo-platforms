# Simulator variant of the FW Demo Platform

fwdemo_sim_platform_inc = include_directories('.')

fwdemo_sim_platform_dep = declare_dependency(
	include_directories: fwdemo_sim_platform_inc,
	dependencies: [
		fwdemo_simulator_hw_platform_dep,
		posix_os_dep,
		logging_subsystem_dep,
		stdlib_native_dep
	],
	sources: files('platform.cpp'),
)

# This is used for running framework components on the host machine when cross compilation is used
if target_architecture == 'x86_64'
	fwdemo_sim_x86_platform_dep = declare_dependency(
		include_directories: fwdemo_sim_platform_inc,
		dependencies: [
			fwdemo_simulator_hw_platform_dep,
			posix_os_dep,
			logging_subsystem_dep,
			stdlib_host_dep
		],
		sources: files('platform.cpp'),
	)
endif
