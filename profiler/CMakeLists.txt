cmake_minimum_required(VERSION 2.8)

# project name
project(profiler)

# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)


# disable the rpath stuff
set(CMAKE_SKIP_BUILD_RPATH FALSE)


# detect the architecture (note: this test won't work for cross-compilation)
    
include(CheckTypeSize)
check_type_size(void* SIZEOF_VOID_PTR)
if("${SIZEOF_VOID_PTR}" STREQUAL "4")
	set(ARCH x86)
elseif("${SIZEOF_VOID_PTR}" STREQUAL "8")
	set(ARCH x64)
else()
	message(FATAL_ERROR "Unsupported architecture")
	return()
endif()

# configure links
set(LIBS)
set(SFML_LIBS sfml-audio sfml-graphics sfml-network sfml-system sfml-window)
set(TBB_LIBS tbb)
set(YCTOOLS_LIBS yctools)
set(DSF_LIBS dsf)

# configure headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers)
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INC
    ${INCROOT}/BouncingCircleManager.h	
	${INCROOT}/MyDSF.h			
	${INCROOT}/SyncFlockingBoid.h
	${INCROOT}/DSFSFML.h		
	${INCROOT}/RandomCircleManager.h	
	${INCROOT}/SyncVector3D.h
	${INCROOT}/ResourcePath.hpp	
	${INCROOT}/Vector3D.h
	${INCROOT}/FPS.h			
	${INCROOT}/SyncBouncingCircle.h
	${INCROOT}/FlockingBoidManager.h	
	${INCROOT}/SyncCircle.h
)

# configure source
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC
    ${SRCROOT}/BouncingCircleManager.cpp
	${SRCROOT}/DSFSFML.cpp			
	${SRCROOT}/SyncBouncingCircle.cpp		
	${SRCROOT}/SyncCircle.cpp
	${SRCROOT}/FPS.cpp				
	${SRCROOT}/SyncFlockingBoid.cpp
	${SRCROOT}/FlockingBoidManager.cpp		
	${SRCROOT}/SyncVector3D.cpp
	${SRCROOT}/MyDSF.cpp			
	${SRCROOT}/Vector3D.cpp
	${SRCROOT}/RandomCircleManager.cpp		
	${SRCROOT}/main.cpp
)
if (MSVC)
	# Windows VC
	# Activate C++ exception handling
	if (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif ()

	# Set Warning level always to 4
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else ()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif () 

	# Add Math definitions
	add_definitions(-D_USE_MATH_DEFINES)


	# Add Links
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/libs)
    set(LIBRARIES ${TBB_LIBS} ${YCTOOLS_LIBS} ${DSF_LIBS} ${SFML_LIBS}) 
    foreach(lib ${LIBRARIES})
        set(LIBS ${LIBS} ${lib}.lib)
    endforeach()

	# Add Source
	set(SRC ${SRC} ${SRCROOT}/ResourcePath.cpp)

	add_executable(${PROJECT_NAME} ${INC} ${SRC})
    target_link_libraries(${PROJECT_NAME} ${LIBS})
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy_directory
						"${PROJECT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/dlls"
						$<TARGET_FILE_DIR:${PROJECT_NAME}>)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy_directory
						"${PROJECT_SOURCE_DIR}/resource"
						$<TARGET_FILE_DIR:${PROJECT_NAME}>)
elseif(APPLE)
	# Mac OS X Xcode
    set(CMAKE_MACOSX_RPATH 1)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx/tbb)
    find_library(YCTOOLS_LIBRARY NAMES yctools PATHS ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx/yctools)
	ADD_DEFINITIONS(
    		-std=c++11
	)
    	foreach(lib ${TBB_LIBRARY})
        	set(LINK_LIBRARY
        		${LINK_LIBRARY}
       	 		optimized ${lib}.dylib
        		debug ${lib}_debug.dylib
        	)
    	endforeach()
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
	# Unix
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-unix/${ARCH})
	ADD_DEFINITIONS(
    		-std=c++11
	)
endif()


set_target_properties(
    ${EXECUTABLE_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)