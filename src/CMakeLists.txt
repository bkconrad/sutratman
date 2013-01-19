option(DEDICATED "Build a dedicated server (no need for client-side libs")

set(SUT_LIBRARIES )
set(SUT_INCLUDE_DIRS )

include_directories(${CMAKE_SOURCE_DIR}/lib/tnl)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/lib/tomcrypt)

aux_source_directory(${CMAKE_SOURCE_DIR}/src/shared SHARED_SOURCES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/server SERVER_SOURCES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/client CLIENT_SOURCES)

# manually add main file since it's in src/
set(SHARED_SOURCES ${SHARED_SOURCES} main)

if(DEDICATED)
	add_executable(sutratman ${SERVER_SOURCES} ${SHARED_SOURCES})
	add_definitions(-DSUT_DEDICATED)
else()
	add_executable(sutratman ${CLIENT_SOURCES} ${SERVER_SOURCES} ${SHARED_SOURCES})
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
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(SYSTEM ${SUT_INCLUDE_DIRS})
