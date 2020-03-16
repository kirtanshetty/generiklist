cmake_minimum_required(VERSION 2.8)
project(daemonmonitor)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  cmake_policy(SET CMP0068 NEW)
  SET(CMAKE_MACOSX_RPATH ON)
  SET(CMAKE_INSTALL_RPATH "@loader_path")
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  SET(PLATFORM_LINKER_FLAGS "-Wl,-dead_strip -s")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(PLATFORM_LINKER_FLAGS "-Wl,-rpath,./ -s -Wl,--gc-sections -Wl,--as-needed -lpthread")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

endif()

SET(CMAKE_C_FLAGS "-std=c11")
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath \$<))\"'")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

FILE(GLOB SOURCES_TEST_DEMO "test/demo.cpp")

ADD_EXECUTABLE(test_genericklist ${SOURCES_TEST_DEMO})

TARGET_LINK_LIBRARIES(test_genericklist ${PLATFORM_LINKER_FLAGS})
