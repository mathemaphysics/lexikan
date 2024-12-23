set( target ${PROJECT_NAME} )

set (
    sources
        Base.cpp
        IHasUUID.cpp
)

set (
    headers
        Base.hpp
        IHasUUID.hpp
)

# Create a library target
add_library(
    "${PROJECT_NAME}Base"
    SHARED
        ${sources}
        ${headers}
)

# Specify the include directories for the library
target_include_directories(
    "${PROJECT_NAME}Base"
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
    "${PROJECT_NAME}Base"
        Boost::system
)

if (BUILD_HWIFC)
    add_subdirectory(hwifc)
endif()

if (BUILD_PLUGIN)
    add_subdirectory(plugin)
endif()

if (BUILD_PYTHON)
    add_subdirectory(python)
endif()

# Specify the properties for the library
set_target_properties(
    "${PROJECT_NAME}Base"
    PROPERTIES
        VERSION
            ${PROJECT_VERSION}
        SOVERSION
            1
        EXPORT_NAME
            "${PROJECT_NAME}Base"
)
