######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#Generate and install pkg-config file
configure_file(htopml.pc.in ${CMAKE_CURRENT_BINARY_DIR}/htopml.pc ESCAPE_QUOTES @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/htopml.pc DESTINATION share/pkgconfig)
