# Sensor Hub 

A bare metal sensor hub utilizing the following sensors: acceleromter, gyroscope, pressure, & humidity.

## Hardware

This project uses the STM32 IoT Discovery Kit, Part number: V-L475E-IOTA.

## Building, Flashing, & Running with st-util

1. Run 'make' in project directory

2. Run 'st-link' to start GDB server

3. In a separate terminal, run 'arm-none-eabi-gdb <./project/build/project_name.elf>'

    a. Run gdb command 'tar extended-remote :4242'
    
    b. Run gdb command 'load'

    c. Run gdb command 'continue' to begin execution

## Potential Future Features

Some features I may add to this project in the future:

- Bare metal vs RTOS implementation

- Wifi/BLE data upload

- Data upload, & data ingestion

- Low power mode

- Automated build, CI, testing

- Bootloader

- OTA bootloader

- Secure boot

- TDD


