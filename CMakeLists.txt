cmake_minimum_required(VERSION 3.10:)
project(SharedPtr)

set(CMAKE_CXX_STANDARD 17)
add_library(shared_ptr INTERFACE)


add_executable(main sources/main.cpp)

target_include_directories(
  shared_ptr
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(main shared_ptr)
