######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
if (NOT GTEST_FOUND)
	set(DISABLE_TESTS "yes")
endif (NOT GTEST_FOUND)

######################################################
print_variable_status("ENABLE_JUNIT_OUTPUT")
print_variable_status("ENABLE_VALGRIND")
print_variable_status("DISABLE_TESTS")
print_variable_status("ENABLE_GCC_COVERAGE")