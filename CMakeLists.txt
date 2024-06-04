# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
   set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(PICO_SDK_PATH ${USERHOME}/.pico-sdk/sdk/1.5.1)
set(PICO_TOOLCHAIN_PATH ${USERHOME}/.pico-sdk/toolchain/13_2_Rel1)
if(WIN32)
    set(pico-sdk-tools_DIR ${USERHOME}/.pico-sdk/tools/1.5.1)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config.cmake)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config-version.cmake)
endif()
# ====================================================================================
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
   set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(PICO_SDK_PATH ${USERHOME}/.pico-sdk/sdk/1.5.1)
set(PICO_TOOLCHAIN_PATH ${USERHOME}/.pico-sdk/toolchain/13_2_Rel1)
if(WIN32)
    set(pico-sdk-tools_DIR ${USERHOME}/.pico-sdk/tools/1.5.1)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config.cmake)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config-version.cmake)
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "pico_w")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(keyboard C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(keyboard keyboard.c)

pico_set_program_name(keyboard "keyboard")
pico_set_program_version(keyboard "0.1")

# Generate PIO header
pico_generate_pio_header(keyboard ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(keyboard 1)
pico_enable_stdio_usb(keyboard 0)

# Add the standard library to the build
target_link_libraries(keyboard
        tinyusb_device
        tinyusb_board
        btstack
        pico_stdlib)


# Add the standard include files to the build
target_include_directories(keyboard PRIVATE
${CMAKE_CURRENT_LIST_DIR}

# hals
${CMAKE_CURRENT_LIST_DIR}/keyboard_helper/hals/
${CMAKE_CURRENT_LIST_DIR}/keyboard_helper/hals/usb_interface/tusb

# keyboard profiles
${CMAKE_CURRENT_LIST_DIR}/keyboard_helper/keyboard_profiles

# layout
${CMAKE_CURRENT_LIST_DIR}/keyboard_helper/layout

${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required

)

# Add any user requested libraries
target_link_libraries(keyboard 
        hardware_i2c
        hardware_pio
        hardware_timer
        hardware_watchdog
        pico_cyw43_arch_none
        )



pico_add_extra_outputs(keyboard)

