# stm32-minimal-l475

This project is a minimal development environment for STM32 L475; STM32 IoT Discovery Kit

This is a slight adaptation of  [STM32 Minimal Development Environment](https://www.purplealienplanet.com/node/69).

## Requirements
[STM32CubeL4 from ST](https://www.st.com/en/embedded-software/stm32cubel4.html). Copy the 'Drivers' directory to the 'Drivers' directory in this project.

## Building, Flashing, & Running with st-util

1. Run 'make' in project directory

2. Run 'st-link' to start GDB server

3. In a separate terminal, run 'arm-none-eabi-gdb <./project/build/project_name.elf>'

    a. Run gdb command 'tar extended-remote :4242'
    
    b. Run gdb command 'load'

    c. Run gdb command 'continue' to begin execution

