cmake_minimum_required(VERSION 3.16)
project(Astrid VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE Generator: ${CMAKE_GENERATOR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ASTRL_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE SPACE_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "test/main.cpp")

add_library(ASTRL STATIC ${ASTRL_SOURCES})

# create executable
add_executable(Astrid ${SPACE_SOURCES})

# link glfw3 library and opengl library
target_link_libraries(ASTRL PUBLIC ${OPENGL_LIBRARIES} glfw GLEW::GLEW glm::glm)

# link ASTRLLibrary 
target_link_libraries(Astrid PUBLIC ASTRL)