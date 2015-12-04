cmake_minimum_required(VERSION 2.6)
project(BlackLib)
set(BlackLib_VERSION_MAJOR 3)
set(BlackLib_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "-D__GXX_EXPERIMENTAL_CXX0X__ -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 -std=c++0x -O0 -g3 -Wall -fmessage-length=0")

find_package(Threads)

include_directories(/usr/arm-linux-gnueabi/include/c++/4.6.3)

set(BLACK_SRC src/BlackCore.cpp
src/BlackPWM/BlackPWM.cpp
src/BlackDirectory/BlackDirectory.cpp
src/BlackSPI/BlackSPI.cpp
src/BlackTime/BlackTime.cpp
src/BlackUART/BlackUART.cpp
src/BlackGPIO/BlackGPIO.cpp
src/BlackMutex/BlackMutex.cpp
src/BlackI2C/BlackI2C.cpp
src/BlackADC/BlackADC.cpp
src/BlackThread/BlackThread.cpp
)

include_directories(include)

add_library(BlackLib SHARED ${BLACK_SRC})

install(TARGETS BlackLib LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/BlackLib)
