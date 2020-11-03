oled_subproject = subproject('two-tone-oled')
ssd1306_native_driver_dep = oled_subproject.get_variable('ssd1306_native_driver_dep')
ssd1306_driver_dep = oled_subproject.get_variable('ssd1306_driver_dep')

nucleo_l4r5zi_fwdemo_hw_platform_dep = declare_dependency(
	include_directories: include_directories('.'),
	sources: files('NucleoL4R5ZI_fwdemo_HWPlatform.cpp'),
	dependencies: [
		stm32l4r5_processor_dep,
		ssd1306_driver_dep,
		st_vl53l1x_driver_dep
	]
)
