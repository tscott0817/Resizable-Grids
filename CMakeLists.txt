cmake_minimum_required( VERSION 3.1 )

project( Grid )

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

#set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
#set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory( glfw glew )

set( GRID-SRC
     main.cpp
     )

add_executable( Grid WIN32 ${GRID-SRC} GL/glew.h glew.c GL/wglew.h window.h window.cpp components/grid/grid.h
                components/grid/grid.cpp components/primitiveShapes/shape.h components/primitiveShapes/shape.cpp
                components/primitiveShapes/rect.h components/primitiveShapes/rect.cpp)

target_link_libraries( Grid ${OPENGL_LIBRARIES} glfw OpenGL::GL)

