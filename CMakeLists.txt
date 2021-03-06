######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#Cmake basic options
cmake_minimum_required(VERSION 2.6)
project(htopml)
set(HTMLTOP_VERSION "0.1.0")

######################################################
#global setup
enable_testing()
add_definitions(-DVERSION="${HTMLTOP_VERSION}")

######################################################
#Add internal search path for scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

######################################################
#Delegate some cmake scripts
include(${CMAKE_SOURCE_DIR}/cmake/user-options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpack-options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/check-deps.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/enable-options.cmake)

######################################################
#some include dirs
include_directories(${CMAKE_SOURCE_DIR}/extern-deps/mongoose)
include_directories(src/libhtopml/common src/libhtopml/htopml src/libhtopml/http-nodes src/libhtopml/json src/libhtopml/server)

######################################################
#manage subdirs
add_subdirectory(extern-deps)
add_subdirectory(src)
if (NOT DISABLE_TESTS)
	add_subdirectory(tests)
endif (NOT DISABLE_TESTS)
