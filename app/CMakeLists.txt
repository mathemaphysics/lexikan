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
        $<$<BOOL:${WITH_JSONCPP}>:${JSONCPP_LIBRARIES}>
        "${PROJECT_NAME}Base"
)

# Specify the include directories for the library
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
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
