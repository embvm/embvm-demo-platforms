# meson build for nrf52840 USB dongle HW platform

# TODO: this should buidl as a library, not a dependency. Higher levels don't
# need (OR GET!) specific hardware access
nrf52dk_fwdemo_hw_platform = declare_dependency(
	include_directories: include_directories('.'),
	sources: [
		files('nrf52dk_fwdemo_hw_platform.cpp')
	],
	dependencies: [
		nrf52840_processor_dep,
		ssd1306_driver_dep,
		st_vl53l1x_driver_dep,
	]
)
