cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set (CMAKE_CXX_STANDARD 17)

set(MX_Defines_Syms 
	USE_HAL_DRIVER 
	STM32F429xx
    $<$<CONFIG:Debug>:DEBUG>
)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME F330)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM CXX)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    #STM32F429xx
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)


# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    freeRTOS/include
    freeRTOS/portable
    Tasks
    Utils/TinyPrintf
    Devices
    portHAL
    portHAL/portSTM32
    BSP
    #ThirdParty/TinyPrintf
    #ThirdParty/Cli
)



file(GLOB SRC_FILES CONFIGURE_DEPENDS
    #Core/*.c
    freeRTOS/*.c
    freeRTOS/portable/*.c
    freeRTOS/MemMang/*.c
    Tasks/*.cpp
    Utils/TinyPrintf/*.c
    Devices/*.c
    portHAL/*.cpp
    portHAL/portSTM32/*.cpp
    portHAL/*.c
    portHAL/portSTM32/*.c
    BSP/*.cpp
    #ThirdParty/TinyPrintf/*.c
    #ThirdParty/Cli/*.c
    #GR/Device/*.cpp
    #GR/Module/*.cpp
    #GR/Utility/*.cpp

)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${SRC_FILES}
)



# Convert output to hex and binary
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)