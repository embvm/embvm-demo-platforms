# meson build for nrf52840 USB dongle HW platform

# TODO: this should build as a library, not a dependency. Higher levels don't
# need (OR GET!) specific hardware access
nf52dk_blinky_hw_platform_dep = declare_dependency(
	include_directories: include_directories('.'),
	sources: [files('nrf52dk_blinky_hw_platform.cpp')],
	dependencies: [
		nrf52840_processor_dep,
	]
)
