cmake_minimum_required(VERSION 2.6)
project(BlackLib)
set(BlackLib_MAJOR_VERSION 3)
set(BlackLib_MINOR_VERSION 0)
set(BlackLib_PATCH_VERSION 0)
set(BlackLib_VERSION ${BlackLib_MAJOR_VERSION}.${BlackLib_MINOR_VERSION}.${BlackLib_PATCH_VERSION})

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules")

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

# Package Configuration, based on examples from OctoMap and
# Pronto
# uninstall target
configure_file(
    "${PROJECT_SOURCE_DIR}/CMakeModules/CMakeUninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

export(PACKAGE BlackLib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(BlackLib_INCLUDE_DIRS "${INCLUDE_DIRS}")
set(BlackLib_LIB_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
# not used right now (export depends?)
#set(BlackLib_CMAKE_DIR "${PROJECT_BINARY_DIR}")
configure_file(blacklib-config.cmake.in
  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/blacklib/blacklib-config.cmake" @ONLY)
configure_file(blacklib-config-version.cmake.in
  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/blacklib/blacklib-config-version.cmake" @ONLY)

install(FILES
  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/blacklib/blacklib-config.cmake"
  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/blacklib/blacklib-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/blacklib/)

# Write pkgconfig-file:
include(InstallPkgConfigFile)
install_pkg_config_file(blacklib
    CFLAGS
    LIBS -lblacklib
    REQUIRES
    VERSION ${BlackLib_VERSION})
