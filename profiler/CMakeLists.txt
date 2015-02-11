set(EXECUTABLE_NAME profiler)

if(APPLE)
 	set(LIB_DIR ${CMAKE_BINARY_DIR}/extlib/osx)
        find_library(LIBRARIES NAMES 
		dsf 
		yctools 
		freetype 
		sfml-audio
		sfml-graphics
		sfml-network
		sfml-system
		sfml-window
		sndfile
		PATHS ${DSF_DIR})
    	set_source_files_properties(
        	${LIBRARIES}
 		PROPERTIES
        	MACOSX_PACKAGE_LOCATION Frameworks
    	)
    	add_executable(${EXECUTABLE_NAME} MACOSX_BUNDLE "main.cpp" ${LIBRARIES})
        target_link_libraries(${EXECUTABLE_NAME} ${LIBRARIES})
else()
    	add_executable(${EXECUTABLE_NAME} "main.cpp")
endif()

set_target_properties(
    ${EXECUTABLE_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)