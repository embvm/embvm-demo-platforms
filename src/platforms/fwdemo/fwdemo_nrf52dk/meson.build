# Simulator variant of the FW Demo Platform

fwdemo_nrf52dk_platform_inc = include_directories('.')

fwdemo_nrf52dk_platform_dep = declare_dependency(
	include_directories: fwdemo_nrf52dk_platform_inc,
	dependencies: [
		framework_dep,
		nrf52_freertos_dep,
		freertos_embvm_dep,
		freertos_heap3_dep,
		nrf52dk_fwdemo_hw_platform,
		libmemory_freelist_dep,
	],
	link_args: [
		'-L' + meson.current_source_dir(),
		'-Tblinky_gcc_nrf52.ld',
	],
	sources: files('platform.cpp'),
)

# Compilation target for CI purposes
if(meson.is_subproject() == false)
	fwdemo_nrf52dk_platform = static_library('fwdemo_nrf52dk_platform',
		dependencies: fwdemo_nrf52dk_platform_dep,
	)
endif
