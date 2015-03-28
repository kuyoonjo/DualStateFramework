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

# links
set(SFML_LIBS sfml-audio sfml-graphics sfml-network sfml-system sfml-window)
set(DSF_LIBS tbb yctools dsf)
set(LIBS ${SFML_LIBS} ${DSF_LIBS})

# headers
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

# source
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

# resources
set(RESRCROOT ${PROJECT_SOURCE_DIR}/resource)

# os configurations
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

	# Add Source
	set(SRC ${SRC} ${SRCROOT}/ResourcePath.cpp)
	add_executable(${PROJECT_NAME} ${INC} ${SRC})
	# Add Links
    set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/libs)
    set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/dlls)
	set(DEPENDENCIES_TARGET_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)
	set(RESOURCES_TARGET_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources)

elseif(APPLE)
	# Mac OS X Xcode
    set(CMAKE_MACOSX_RPATH 1)
	ADD_DEFINITIONS(-std=c++11)
	
	# Add Source
	set(SRC ${SRC} ${SRCROOT}/ResourcePath.mm)
	add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${INC} ${SRC})
	# Add Links
	SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
	           XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS @executable_path/../Frameworks/)
	set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx)
	set(DEPENDENCIES_DIR ${LIBS_DIR})
	set(LIBS ${LIBS} SFML)
	set(DEPENDENCIES_TARGET_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks)
	set(RESOURCES_TARGET_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources)
else()
	# Unix
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-unix/${ARCH})
	ADD_DEFINITIONS(
    		-std=c++11
	)
endif()


foreach(LIB ${LIBS})
	find_library(LIB_${LIB} NAMES ${LIB} PATHS ${LIBS_DIR})
	target_link_libraries(${PROJECT_NAME} ${LIB_${LIB}})
endforeach()

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)

# copy dependencies and resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${DEPENDENCIES_DIR}
					${DEPENDENCIES_TARGET_DIR})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					"${PROJECT_SOURCE_DIR}/resource"
					${RESOURCES_TARGET_DIR})