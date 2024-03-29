project('embvm-demo-platforms',
	['c', 'cpp'],
	default_options : [
		'warning_level=3',
		'werror=false',
		# This project defaults to a release build
		'debug=false',
		'optimization=2',
		# `build.*` options affect `native: true targets`
		# plain options affect `native: false` targets.
		'c_std=c11', 'build.c_std=c11',
		'cpp_std=c++17', 'build.cpp_std=c++17',
	],
	meson_version: '>=0.58.0',
	version: '1.0'
)

################################
# Project Options and Settings #
################################

# Pick up our common compiler variables + desired_*_flags variables
subdir('meson/compiler')
subdir('meson/compiler/c')
subdir('meson/compiler/cpp')

if get_option('debug')
	add_project_arguments('-DDEBUG',
		language: ['c', 'cpp'])
	add_project_arguments('-DDEBUG',
		language: ['c', 'cpp'], native: true)
endif

if get_option('disable-builtins')
	desired_common_compile_flags += '-fno-builtin'
endif

if get_option('disable-stack-protection')
	desired_common_compile_flags += '-fno-stack-protector'
endif

if get_option('disable-rtti')
	desired_cpp_compile_flags += '-fno-rtti'
	desired_native_cpp_compile_flags += '-fno-rtti'
endif

if get_option('disable-exceptions')
	desired_cpp_compile_flags += ['-fno-exceptions', '-fno-unwind-tables']
	desired_native_cpp_compile_flags += ['-fno-exceptions', '-fno-unwind-tables']
endif

if get_option('enable-pedantic')
	desired_common_compile_flags += '-pedantic'
else
	desired_common_compile_flags += '-Wno-pedantic'
endif

if get_option('enable-pedantic-error')
	desired_common_compile_flags += '-pedantic-error'
endif

compile_settings_list = [
	{'lang': 'c', 'compiler': host_c_compiler, 'flags': desired_c_compile_flags, 'isnative': false},
	{'lang': 'c', 'compiler': native_c_compiler, 'flags': desired_native_c_compile_flags, 'isnative': true},
	{'lang': 'cpp', 'compiler': host_cpp_compiler, 'flags': desired_cpp_compile_flags, 'isnative': false},
	{'lang': 'cpp', 'compiler': native_cpp_compiler, 'flags': desired_native_cpp_compile_flags, 'isnative': true},
]

link_settings_list = [
	{'lang': 'c', 'compiler': host_c_compiler, 'flags': [], 'isnative': false},
	{'lang': 'c', 'compiler': native_c_compiler, 'flags': [], 'isnative': true},
	{'lang': 'cpp', 'compiler': host_cpp_compiler, 'flags': [], 'isnative': false},
	{'lang': 'cpp', 'compiler': native_cpp_compiler, 'flags': [], 'isnative': true},
]

# Process the compilation flags
subdir('meson/compiler/check-and-apply-flags')

#################
# Build Modules #
#################

# Include reusable build modules here via subdir() calls
subdir('meson/linker/linker-script-as-property')
subdir('meson/linker/linker-map')
subdir('meson/test/cmocka')
subdir('meson/objcopy')

###############
# Subprojects #
###############

nordic_subproject = subproject('nordic')
nrf52840_processor_dep = nordic_subproject.get_variable('nrf52840_processor_dep')
nrf52_freertos_dep = nordic_subproject.get_variable('nrf52_freertos_dep')

stm32l4_subproject = subproject('stm32l4')
stm32l4r5_processor_dep = stm32l4_subproject.get_variable('stm32l4r5_processor_dep')

freertos_interface_subproject = subproject('freertos-interface')
freertos_embvm_dep = freertos_interface_subproject.get_variable('freertos_embvm_dep')
freertos_heap3_dep = freertos_interface_subproject.get_variable('freertos_heap3_dep')

embvm_core_subproject = subproject('embvm-core')
framework_dep = embvm_core_subproject.get_variable('framework_dep')
framework_threadless_dep = embvm_core_subproject.get_variable('framework_threadless_dep')
framework_native_dep = embvm_core_subproject.get_variable('framework_native_dep')
simulator_driver_dep = embvm_core_subproject.get_variable('simulator_driver_dep')
simulator_processor_dep = embvm_core_subproject.get_variable('simulator_processor_dep')
posix_os_dep =  embvm_core_subproject.get_variable('posix_os_dep')
logging_subsystem_dep = embvm_core_subproject.get_variable('logging_subsystem_dep')

libmemory_subproject = subproject('libmemory')
libmemory_freelist_dep = libmemory_subproject.get_variable('libmemory_freelist_dep')

aardvark_subproject = subproject('aardvark')
aardvark_native_driver_dep = aardvark_subproject.get_variable('aardvark_native_driver_dep')

vl53l1x_subproject = subproject('st-vl53l1x')
st_vl53l1x_driver_dep = vl53l1x_subproject.get_variable('st_vl53l1x_driver_dep')
st_vl53l1x_native_driver_dep = vl53l1x_subproject.get_variable('st_vl53l1x_native_driver_dep')
st_vl53l1x_files_dep = vl53l1x_subproject.get_variable('st_vl53l1x_files_dep')

oled_subproject = subproject('two-tone-oled')
ssd1306_native_driver_dep = oled_subproject.get_variable('ssd1306_native_driver_dep')
ssd1306_driver_dep = oled_subproject.get_variable('ssd1306_driver_dep')

#######################
# Process Source Tree #
#######################

# Add files to this variable if you want them analyzed by clang-tidy
clangtidy_files = []
# Add dependencies to this array for testing with Catch2
#catch2_tests_dep = []

subdir('src')

# Defined after src and test so catch2_dep is fully populated
# when creating the built-in targets
#subdir('meson/test/catch2')

###################
# Tooling Modules #
###################

clangformat_targets = ['src']

subdir('meson/analysis/clang-tidy')
subdir('meson/analysis/complexity')
subdir('meson/analysis/cppcheck')
subdir('meson/analysis/sloccount')
subdir('meson/analysis/vale')
subdir('meson/format')
subdir('meson/docs/doxygen')

#############
# Packaging #
#############

# These macros allow you to simplify the declaration of includes for common
# include paths. Examples:
#	build_root_include.format('doc'),
#	app_include.format('APP')
build_root_include = meson.project_build_root() + ':@0@'
app_include = meson.project_build_root() / 'src/app:@0@'
lib_include = meson.project_build_root() / 'src/lib:@0@'

host_pkg_files = [
	build_root_include.format('docs'),
	app_include.format('APP')
]

native_pkg_files = [
	build_root_include.format('docs'),
	app_include.format('APP_native')
]

# Invoke the package module
subdir('meson/package')
