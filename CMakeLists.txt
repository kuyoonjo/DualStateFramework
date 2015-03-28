cmake_minimum_required(VERSION 2.8)

# project name
project(dsf)

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

# configure links and headers

set(LIBS tbb yctools) 

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

    set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/libs)
elseif(APPLE)
	# Mac OS X Xcode
    set(CMAKE_MACOSX_RPATH 1)
    set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-osx)
    OPTION(OSX_FRAMEWORK "Build a Mac OS X Framework")
	ADD_DEFINITIONS(
    		-std=c++11
	)
else()
	# Unix
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-unix/${ARCH})
	ADD_DEFINITIONS(
    		-std=c++11
	)
endif()

# Source
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/dsf/include)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/dsf/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dsf)
# add the header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers)
include_directories(${INCROOT})

# output
add_library (${PROJECT_NAME} SHARED ${DSF_INC} ${DSF_SRC})
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)

if(OSX_FRAMEWORK)
    set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        MACOSX_FRAMEWORK_IDENTIFIER ie.itcarlow.yuchen.dsf
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        PUBLIC_HEADER "${DSF_INC}"
    )
endif()

foreach(LIB ${LIBS})
	find_library(LIB_${LIB} NAMES ${LIB} PATHS ${LIBS_DIR})
    set_source_files_properties(${LIB_${LIB}} PROPERTIES MACOSX_PACKAGE_LOCATION Frameworks)
	target_link_libraries(${PROJECT_NAME} ${LIB_${LIB}})
endforeach()