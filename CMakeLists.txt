cmake_minimum_required( VERSION 3.1 )

project( Grid )

find_package( OpenGL REQUIRED )
#find_package( GLEW REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( glfw glew )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set( GRID-SRC
     main.cpp
     )

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glew/include/GL)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/glew/lib)

add_executable( Grid WIN32 ${GRID-SRC} GL/glew.h glew.c GL/wglew.h components/grid/grid.h components/grid/grid.cpp
                components/primitiveShapes/shape.h components/primitiveShapes/shape.cpp components/primitiveShapes/rect.h
                components/primitiveShapes/rect.cpp)

target_link_libraries( Grid ${OPENGL_LIBRARIES} glfw )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'Grid' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Grid )
    endif()
endif()
