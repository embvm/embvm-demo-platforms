# meson build for framework internal Platform definitions

subdir('blinky_base')

if host_machine.cpu_family() == 'arm' and meson.get_compiler('cpp', native: false).get_id() == 'gcc'
subdir('blinky_nrf52dongle')
subdir('blinky_nrf52dk')
endif

if get_option('enable-threading') == true
subdir('blinky_sim')
endif
