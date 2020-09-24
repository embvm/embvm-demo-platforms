# Simulator variant of the FW Demo Platform

blinky_nrf52dk_platform_inc = include_directories('.')

blinky_nrf52dk_platform_dep = declare_dependency(
	include_directories: blinky_nrf52dk_platform_inc,
	dependencies: [
		nf52dk_blinky_hw_platform_dep,
		blinky_demo_platform_dep,
		libmemory_freelist_dep,
		libc_dep,
		libcxxabi_dep,
		libcxx_full_dep,
		compiler_rt_builtins_dep,
	],
	link_args: [
		'-L' + meson.current_source_dir(),
		'-Tblinky_gcc_nrf52.ld',
	],
	sources: files('platform.cpp'),
)
