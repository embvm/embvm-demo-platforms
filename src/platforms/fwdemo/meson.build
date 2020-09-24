# meson build for framework internal Platform definitions

if enable_threading == true

	subdir('fwdemo_sim')

	if target_architecture == 'arm' and target_compiler_id == 'gcc'
		subdir('fwdemo_nrf52dk')
	endif

endif
