add_executable(Proyecto
        Proyecto.c
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(Proyecto pico_stdlib hardware_i2c)
pico_enable_stdio_usb(Proyecto 1)
pico_enable_stdio_uart(Proyecto 1)
# create map/bin/hex file etc.
pico_add_extra_outputs(Proyecto)

# add url via pico_set_program_url
example_auto_set_url(Proyecto)
