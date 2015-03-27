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

set(TBB_LIBRARY libtbb) 
set(LINK_LIBRARY)

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

    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/tbb)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-msvc/${ARCH}/yctools)
    set(TBB_LIBRARY tbb) 
    set(YCTOOLS_LIBRARY yctools)
    foreach(lib ${TBB_LIBRARY})
        set(LINK_LIBRARY
        ${LINK_LIBRARY}
        optimized ${lib}.lib
        debug ${lib}_debug.lib
        )
    endforeach()
    foreach(lib ${YCTOOLS_LIBRARY})
        set(LINK_LIBRARY
        ${LINK_LIBRARY}
        optimized ${lib}.lib
        debug ${lib}.lib
        )
    endforeach()
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
else()
	# Unix
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/libs-unix/${ARCH})
	ADD_DEFINITIONS(
    		-std=c++11
	)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers)

# library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dsf)
if(APPLE)
    OPTION(OSX_FRAMEWORK "Build a Mac OS X Framework")
endif()


# installation
if(WINDOWS)
	install(TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION bin COMPONENT dsf ARCHIVE DESTINATION lib COMPONENT dsf)
else()
	install(TARGETS ${OUTPUT_NAME} DESTINATION lib COMPONENT dsf)
endif()
# headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/dsf DESTINATION include)