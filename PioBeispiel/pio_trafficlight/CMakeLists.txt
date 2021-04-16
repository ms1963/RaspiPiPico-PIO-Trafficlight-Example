add_executable(pio_trafficlight)

# by default the header is generated into the build dir
pico_generate_pio_header(pio_trafficlight ${CMAKE_CURRENT_LIST_DIR}/pio_trafficlight.pio)
# however, alternatively you can choose to generate it somewhere else (in this case in the source tree for check in)
#pico_generate_pio_header(pio_trafficlight ${CMAKE_CURRENT_LIST_DIR}/pio_trafficlight.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_sources(pio_trafficlight PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pio_trafficlight.c)

pico_enable_stdio_uart(pio_trafficlight 1)
pico_enable_stdio_usb(pio_trafficlight 1)

target_link_libraries(pio_trafficlight PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_trafficlight)

# add url via pico_set_program_url
example_auto_set_url(pio_trafficlight)