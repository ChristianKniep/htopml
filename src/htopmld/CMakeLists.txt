######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#build htopmld exe (for tests)
add_executable(htopmld main.cpp)
target_link_libraries(htopmld htopml)
target_link_libraries(htopmld ${CMAKE_THREAD_LIBS_INIT})

######################################################
INSTALL(TARGETS htopmld
        RUNTIME DESTINATION bin)
