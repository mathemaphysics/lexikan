
set( target ${PROJECT_NAME} )

set (
    sources
        lexikan.cpp
)

set (
    headers
        lexikan.hpp
)

# Create a library target
add_executable(
    ${PROJECT_NAME}
        ${sources}
        ${headers}
)

# Link to the happy places
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        Boost::program_options
        Boost::system
        spdlog::spdlog
)

# Specify the include directories for the library
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# Optionally, link other libraries if needed
target_link_libraries(
    "${PROJECT_NAME}"
    PRIVATE
        "${PROJECT_NAME}Base"
)

# Specify the properties for the library
set_target_properties(
    "${PROJECT_NAME}"
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        EXPORT_NAME ${PROJECT_NAME}
)

# Export the library for other projects to use
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Export the target so that it can be imported by other CMake projects
install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
    FILES
        "${PROJECT_NAME}Config.cmake"
        "${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)
