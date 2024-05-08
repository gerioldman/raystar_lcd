project('raystar_lcd', 'c')

lib = static_library('raystar_lcd',sources: ['src/raystar_lcd.c'],include_directories: ['include'])

lib_dep = declare_dependency(
        include_directories: ['include'],
        link_with: lib
)

meson.override_dependency('raystar_lcd',lib_dep)