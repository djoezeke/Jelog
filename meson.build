# ===================================================================
# Copyright © 2025 Sackey Ezekiel Etrue
# Distributed under the terms of the MIT license.
# ===================================================================

#--------------------------------------------------------------------
# Project and version.
#--------------------------------------------------------------------

project('jelog',
	'cpp',
	version : '0.1.0',
    license : 'MIT',
	default_options : [
		'buildtype=release',
		'default_library=static',
		'cpp_std=c++17'
		]
)


license = files('LICENSE')

incdir = include_directories('include')

compiler = meson.get_compiler('cpp')
message('target cpu_family: @0@'.format(host_machine.cpu_family()))
message('target cpu: @0@'.format(host_machine.cpu()))
message('target system: @0@'.format(host_machine.system()))
message('target endian: @0@'.format(host_machine.endian()))

#--------------------------------------------------------------------
# Configure variables for the library   
#--------------------------------------------------------------------

jelog_is_subproject = meson.is_subproject()

jelog_build_tests = (get_option('jelog_build_tests') ) and not jelog_is_subproject

jelog_build_examples = (get_option('jelog_build_examples') or is_devel) and not jelog_is_subproject

src_files = ['src/jelog.cpp']
if meson.get_option('backend')
	# noop - keep compatibility with meson options
endif

if files('src/jelogc.cpp').length() > 0
	  src_files += 'src/jelogc.cpp'
endif

library_name = 'jelog'

shared_lib = true
jelog_lib = shared_library(library_name, src_files,
	include_directories : incdir,
	install : true,
)

if not meson.is_subproject()

	install_headers('include/jelog/jelog.h', subdir : 'jelog')
	install_headers('include/jelog/jelog.hpp', subdir : 'jelog')

	pkgc = import('pkgconfig')
	pkgc.generate(
		name : meson.project_name(),
		version: meson.project_version(),
		description: 'Logging for Modern C++'
		url: 'https://github.com/djoezeke/jelog',
	)

endif


#--------------------------------------------------------------------
# Add Project subdirectories
#--------------------------------------------------------------------

if jelog_build_tests
	subdir('tests')
endif

if jelog_build_examples
	subdir('examples')
endif

# ===================================================================
