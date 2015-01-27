set(EXECUTABLE_NAME example)
add_executable(
    ${EXECUTABLE_NAME}
    MACOSX_BUNDLE
    "main.cpp")

if(XCODE)
	# Detect and add SFML
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/example/cmake_modules" ${CMAKE_MODULE_PATH})
    #Find any version 2.X of SFML
    #See the FindSFML.cmake file for additional details and instructions
    find_package(SFML REQUIRED system window graphics network audio)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    endif()
endif()

set_target_properties(
    ${EXECUTABLE_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)