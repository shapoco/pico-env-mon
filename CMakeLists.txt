cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico_env_mon C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(pico_env_mon)

target_sources(
    pico_env_mon PRIVATE 
    src/pico_env_mon.cpp 
    src/digit16.cpp 
    src/digit32.cpp 
    src/images.cpp
)

target_link_libraries(pico_env_mon PRIVATE pico_stdlib hardware_spi)
pico_add_extra_outputs(pico_env_mon)
