add_executable(ADC1 ADC1.c)

target_link_libraries(ADC1 pico_stdlib hardware_adc)

# enable uart output, disable usb output
pico_enable_stdio_uart(ADC1 0)
pico_enable_stdio_usb(ADC1 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(ADC1)

# add url via pico_set_program_url
example_auto_set_url(ADC1)

