add_executable(LCDterm
        LCDterm.c
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(LCDterm pico_stdlib hardware_i2c)
pico_enable_stdio_usb(LCDterm 1)
pico_enable_stdio_uart(LCDterm 1)
# create map/bin/hex file etc.
pico_add_extra_outputs(LCDterm)

# add url via pico_set_program_url
example_auto_set_url(LCDterm)
