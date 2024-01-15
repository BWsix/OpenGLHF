cmake_minimum_required(VERSION 3.27)
project("OpenGLHF")

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED COMPONENTS GLEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(glhf main.cpp utils.cpp shaderProgram.cpp camera.cpp)
target_compile_options(glhf PRIVATE "-Wall" "-Wextra" "-ggdb")
target_include_directories(glhf PRIVATE ${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(glhf PRIVATE ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
