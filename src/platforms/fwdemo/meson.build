# meson build for framework internal Platform definitions

#TODO: Update this when enable-threading has been disabled
if get_option('enable-threading') == true

	subdir('fwdemo_sim')

	if host_machine.cpu_family() == 'arm' and meson.get_compiler('cpp', native: false).get_id() == 'gcc'
		subdir('fwdemo_nrf52dk')
	endif
else
	if host_machine.cpu_family() == 'arm' and meson.get_compiler('cpp', native: false).get_id() == 'gcc'
		subdir('fwdemo_nucleo_l4r5zi')
	endif
endif
