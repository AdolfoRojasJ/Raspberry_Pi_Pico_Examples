add_executable(lcd16x2
        lcd16x2.c
        )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(lcd16x2 pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(lcd16x2)

# add url via pico_set_program_url
example_auto_set_url(lcd16x2)
