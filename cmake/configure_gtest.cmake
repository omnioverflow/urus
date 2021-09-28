get_filename_component(CURR_CMAKE_FILE_NAME ${CMAKE_CURRENT_LIST_FILE} NAME)

message("+-------------------------------+")
message("| Processing " ${CURR_CMAKE_FILE_NAME} "   |")
message("+-------------------------------+")

# GoogleTest must be already installed as a standalone project
# (in such case GTEST_ROOT variable must be defined)
# or it can be incorporated into an existing CMake build 
# (define GTEST_FORCE_EXTERNAL for the latter option)
if (NOT DEFINED GTEST_ROOT 
     AND NOT DEFINED ENV{GTEST_ROOT}
     AND NOT DEFINED GTEST_FORCE_EXTERNAL)
	message( 
		"+-----------------------------------------------------------------------------------------+\n"
		"/!\\ Warning /!\\ \n"
		"GTEST_ROOT is not defined. Now, there are three options:\n"
		"1. Specify GTEST_ROOT when running cmake, like this: 'cmake -DGTEST_ROOT=FooBar ... '\n"
		"2. Configure GTEST_ROOT environment variable (see how environmet vars are defined on your OS) \n" 
		"3. Enable GTEST_FORCE_EXTERNAL, like this: 'cmake -DGTEST_FORCE_EXTERNAL=ON ... '\n"
		"+-----------------------------------------------------------------------------------------+\n"
		)
	return()
elseif (NOT DEFINED GTEST_ROOT AND DEFINED ENV{GTEST_ROOT})
	message( "Use environment variable " ENV{GTEST_ROOT} )
	set(GTEST_ROOT ENV{GTEST_ROOT})
endif()

if (DEFINED ${GTEST_ROOT})
	message("Found GTEST_ROOT = " ${GTEST_ROOT})

	find_package(GTest REQUIRED)

	if (NOT GTEST_FOUND)
		message(FATAL_ERROR "GoogleTest not found")
	endif()

	include_directories(${GTEST_INCLUDE_DIRS})
endif()

if (DEFINED GTEST_FORCE_EXTERNAL)
    include(${PROJECT_SOURCE_DIR}/cmake/download_gtest.cmake)
endif() # DEFINED GTEST_FORCE_EXTERNAL
