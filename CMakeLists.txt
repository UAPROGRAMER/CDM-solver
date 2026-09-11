cmake_minimum_required(VERSION 3.20)
project(CDMSolver LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/dest"
)

file(GLOB source CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_executable(cdms ${source})

if(WIN32)
  target_link_options(cdms PRIVATE "-static")
elseif(UNIX AND NOT APPLE)
  target_link_options(cdms PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

target_compile_options(cdms PRIVATE -Wall -Wextra -Wpedantic)