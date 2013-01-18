include_directories(${CMAKE_SOURCE_DIR}/lib/tnl)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/lib/tomcrypt)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SUTRATMAN_SOURCES)
add_executable(sutratman ${SUTRATMAN_SOURCES})

set_target_properties(sutratman
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/exe
)

add_dependencies(sutratman tnl)
target_link_libraries(sutratman tnl)
