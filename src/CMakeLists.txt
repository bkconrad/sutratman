option(DEDICATED "Build a dedicated server (no need for client-side libs")
option(BUILD_TESTS "Build the unit tests too")

set(SUT_LIBRARIES )
set(SUT_INCLUDE_DIRS )

set(SERVER_SOURCES
	entity
	diagnostics
	game
	game_connection
	game_interface
	log
	mathutil
	mobile_entity
	mobile_entity_animator
	player
	server
)
set(CLIENT_SOURCES
	client/client
	client/client_entity
	client/client_game
	client/client_player
	client/diagnosticswindow
	client/gui
	client/guiwindowinterface
	client/input
	client/listenerinterface
)

add_custom_target(doc doxygen Doxyfile
	COMMAND echo "*** Documentation written to ${CMAKE_SOURCE_DIR}/doc ***"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
)

if(DEDICATED)
	add_executable(sutratman main ${SERVER_SOURCES})
	add_definitions(-DSUT_DEDICATED)
else()
	add_executable(sutratman main ${CLIENT_SOURCES} ${SERVER_SOURCES})
	find_package(Irrlicht REQUIRED)
	set(SUT_LIBRARIES ${SUT_LIBRARIES} ${IRRLICHT_LIBRARIES})
	set(SUT_INCLUDE_DIRS ${SUT_INCLUDE_DIRS} ${IRRLICHT_INCLUDE_DIRS})
	add_definitions(${IRRLICHT_DEFINITIONS})
endif()

set_target_properties(sutratman
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/exe
)

add_dependencies(sutratman tnl)
target_link_libraries(sutratman ${SUT_LIBRARIES} tnl)
message(${CMAKE_SOURCE_DIR}/lib/tnl)

include_directories(SYSTEM ${SUT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/lib/gtest/include ${CMAKE_SOURCE_DIR}/lib/tnl ${CMAKE_SOURCE_DIR}/lib/tomcrypt)
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/src)

if(BUILD_TESTS)
	enable_testing()
	aux_source_directory(${CMAKE_SOURCE_DIR}/test TEST_SOURCES)
	add_executable(test_runner ${TEST_SOURCES} ${CLIENT_SOURCES} ${SERVER_SOURCES})
	add_test(test_runner test_runner)
	find_package(Irrlicht)
	include_directories(${CMAKE_SOURCE_DIR}/tnl ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/lib/gtest/include/)
	include_directories(SYSTEM ${IRRLICHT_INCLUDE_DIRS})
	add_definitions(${IRRLICHT_DEFINITIONS})
	target_link_libraries(test_runner gtest gtest_main tnl ${IRRLICHT_LIBRARIES})
	set_target_properties(test_runner PROPERTIES COMPILE_FLAGS "--coverage")
	set_target_properties(test_runner PROPERTIES LINK_FLAGS "--coverage")

	# utility targets for testing
	add_custom_target(coverage ${CMAKE_SOURCE_DIR}/build/src/test_runner
		COMMAND lcov --capture --directory ${CMAKE_SOURCE_DIR} --output-file ${CMAKE_SOURCE_DIR}/build/coverage.info
		COMMAND lcov --extract ${CMAKE_SOURCE_DIR}/build/coverage.info --output-file ${CMAKE_SOURCE_DIR}/build/coverage.info ${CMAKE_SOURCE_DIR}/src/* ${CMAKE_SOURCE_DIR}/src/client/*
		COMMAND genhtml ${CMAKE_SOURCE_DIR}/build/coverage.info --output-directory ${CMAKE_SOURCE_DIR}/build/cov
		DEPENDS test_runner
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build 
	)
endif()
