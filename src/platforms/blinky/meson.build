# meson build for framework internal Platform definitions

subdir('blinky_base')

if target_architecture == 'arm' and target_compiler_id == 'gcc'
subdir('blinky_nrf52dongle')
subdir('blinky_nrf52dk')
endif

if enable_threading == true
subdir('blinky_sim')
endif
