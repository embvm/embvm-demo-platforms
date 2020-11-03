nucleo_l4r5zi_blinky_platform_inc = include_directories('.')

nucleo_l4r5zi_blinky_platform_dep = declare_dependency(
	sources: files('platform.cpp'),
	include_directories: nucleo_l4r5zi_blinky_platform_inc,
	dependencies: [
		nucleo_l4r5zi_blinky_hw_platform_dep,
		framework_threadless_dep,

	],
	link_args: [
		'-L' + meson.current_source_dir(),
		'-Tblinky_gcc_nucleo_l4rzi.ld',
	],
)


# Compilation target for CI purposes
if(meson.is_subproject() == false)
	nucleo_l4r5zi_blinky_platform = static_library('nucleo_l4r5zi_blinky_platform',
		dependencies: nucleo_l4r5zi_blinky_platform_dep,
	)
endif
