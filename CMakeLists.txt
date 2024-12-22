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

set(NYNA_PATH $ENV{NYNA_PATH})
if (NOT NYNA_PATH)
    set(NYNA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../nyna)
endif ()

add_subdirectory(${NYNA_PATH} nyna)

target_include_directories(pico_env_mon
    PRIVATE
        src
)

file(GLOB CPP_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/images/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fonts/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ls027b4/*.cpp
)

target_sources(pico_env_mon
    PRIVATE 
        ${CPP_FILES}
)

target_link_libraries(pico_env_mon
    PRIVATE
        pico_stdlib
        hardware_spi
        nyna
)

pico_enable_stdio_usb(pico_env_mon 1)
pico_enable_stdio_uart(pico_env_mon 0)

pico_add_extra_outputs(pico_env_mon)
