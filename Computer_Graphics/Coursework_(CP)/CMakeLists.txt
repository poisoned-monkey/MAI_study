cmake_minimum_required(VERSION 3.17)
project(kg_kp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(GLAD_DIR "/usr/include/glad")

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(FIG_DIR ${CMAKE_SOURCE_DIR}/figures)
set(CURVE_DIR ${CMAKE_SOURCE_DIR}/curves)
set(MATH_DIR ${CMAKE_SOURCE_DIR}/math)

file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${IMGUI_DIR}/*.cpp
        ${FIG_DIR}/*.cpp
        ${CURVE_DIR}/*.cpp
        ${MATH_DIR}/*.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})
add_library(glad ${GLAD_DIR}/glad.c)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})