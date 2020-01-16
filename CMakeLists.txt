cmake_minimum_required(VERSION 3.5)

project(OnlineDAQ)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})

add_subdirectory(sMDT)

foreach(exec sMDT-server)
    add_executable(${exec} src/${exec}.cxx)
    target_link_libraries(${exec} sMDTLib ${ROOT_LIBRARIES})
endforeach()
