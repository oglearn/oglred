cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(HW_OPENGL)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# Include Files
#########################################################
#add_library(common common/shaderutils.cxx)
include_directories ("${PROJECT_SOURCE_DIR}/common")
#add_subdirectory (common) 
 
# add the executable
add_executable(test01_b01 "${PROJECT_SOURCE_DIR}/ch01/book/1.cpp" "${PROJECT_SOURCE_DIR}/common/shaderutils.cpp")
add_executable(test01_e01 "${PROJECT_SOURCE_DIR}/ch01/exp/1.cpp" "${PROJECT_SOURCE_DIR}/common/shaderutils.cpp")
add_executable(test03_b01 "${PROJECT_SOURCE_DIR}/ch03/book/1.cpp" "${PROJECT_SOURCE_DIR}/common/shaderutils.cpp")

########################################################
# Linking & stuff
#########################################################

# create the program "test"
target_link_libraries(test01_b01 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(test01_e01 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(test03_b01 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
