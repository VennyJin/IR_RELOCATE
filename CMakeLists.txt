cmake_minimum_required(VERSION 2.8.11)

# Project name
project(ir_relocate)

add_compile_options(-std=c++11)
#####################################################
################ PATH DEFINATION ####################


set(WORKSPACE_PATH "${CMAKE_CURRENT_LIST_DIR}/..")
set(CL_OUTPUT_DIRECTORY ${WORKSPACE_PATH}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})


################# INCLUDE DIRECTORIES ##################

include_directories(
    .
    .
    /usr/local
    /usr/local/include/opencv
    /usr/local/include/opencv2
    /usr/include/eigen3
)


# Compiler options
add_definitions(-O2)
add_definitions(-Wall)
# add_definitions(-DNDEBUG)


# Linker options
set(LINK_OPTIONS -lpthread)


# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")


# Define the CXX sources
set ( CXX_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/src/ImageProcess.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/GetLocation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GETTIME/gettime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Comlib_Linux/src/SerialCom.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Comlib_Linux/src/com_lib.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Comlib_Linux/src/com_execute.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Comlib_Linux/src/com_command.cpp

)


set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O2 -Wall")


add_executable(ir_relocate ${CXX_SRCS})


target_link_libraries(ir_relocate ${LINK_OPTIONS})


target_link_libraries(ir_relocate
    /usr/local/lib/libopencv_calib3d.so
    /usr/local/lib/libopencv_core.so
    /usr/local/lib/libopencv_highgui.so
    libopencv_videoio.so
    libopencv_imgcodecs.so
    libopencv_imgproc.so
    /usr/lib/x86_64-linux-gnu/librt.so
    ##/usr/lib/arm-linux-gnueabihf/librt.so
)

