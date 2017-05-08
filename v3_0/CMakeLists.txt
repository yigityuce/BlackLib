cmake_minimum_required(VERSION 3.0)
project(BlackLib)

SET(CMAKE_C_COMPILER   arm-linux-gnueabi-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)

###############################################################################
## file globbing ##############################################################
###############################################################################

# Add sources for library
set(sources ./BlackADC/BlackADC.cpp ./BlackDirectory/BlackDirectory.cpp  ./BlackGPIO/BlackGPIO.cpp ./BlackI2C/BlackI2C.cpp ./BlackMutex/BlackMutex.cpp ./BlackPWM/BlackPWM.cpp ./BlackSPI/BlackSPI.cpp ./BlackThread/BlackThread.cpp ./BlackTime/BlackTime.cpp  ./BlackUART/BlackUART.cpp ./BlackCore.cpp)

# Source for example usage
set(example_sources ./examples.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

# Set compile options for all targets
add_compile_options(-std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -pthread -D__GXX_EXPERIMENTAL_CXX0X__ -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 )

# Set include directories for all targets
include_directories(/usr/arm-linux-gnueabi/include/c++/4.6.3)

add_library(black SHARED ${sources})
set_property(TARGET black PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(black_example ${example_sources})

target_link_libraries(black pthread)

# Link example with libblack
target_link_libraries(black_example pthread black)

# Include directories for black_example only
target_include_directories(black_example PUBLIC ${CMAKE_SOURCE_DIR})
