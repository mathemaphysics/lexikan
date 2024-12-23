cmake_minimum_required(VERSION 3.20)

# Define the project name and version
project(lexikan VERSION 1.0.0)

# Use GNU install directories
include(GNUInstallDirs)

# Configuration options
option( BUILD_PYTHON "Build the python bindings" ON )
option( BUILD_PLUGIN "Build the plugin architecture" ON )
option( BUILD_DOC "Build the documentation" OFF )
option( BUILD_HWIFC "Build hardware interfaces" ON )
option( WITH_JSONCPP "Build with JsonCpp library" ON )
option( WITH_POCO "Build with POCO library" ON )
option( WITH_PYBIND11 "Build pybind11 targets" ON )
option( WITH_LIBUSB "Build with libusb-1.0" ON )

# Configure the headers
configure_file(
    lexikanConfig.hpp.in
    lexikanConfig.hpp
)

# Add the project name
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")

# Find boost; because we still live in 2005
find_package(
	Boost
	REQUIRED
	COMPONENTS
		program_options
		system
)

# Find our logging library
find_package(
	spdlog
	REQUIRED
)

# Need to use PkgConfig to make this work
find_package(
    PkgConfig
)

if (WITH_JSONCPP)
    if (PkgConfig_FOUND)
        # For some reason jsoncpp doesn't have a jsoncppConfig.cmake
        pkg_check_modules(JSONCPP jsoncpp)
        if (JSONCPP_FOUND)
            add_definitions(-DHAVE_JSONCPP)
        endif()
    else()
        # Can't check for jsoncpp without pkg-config
        message(STATUS "Cannot check for jsoncpp without pkg-config")
        set(WITH_JSONCPP OFF)
    endif()
endif()

if (WITH_POCO)
    find_package(
        Poco
        COMPONENTS
            Net
    )
    if (Poco_FOUND)
        add_definitions(-DHAVE_POCO)
    endif()
endif()

# Find python items because we'll build the python bindings
if (BUILD_PYTHON)
    # Find python development and numpy libraries
    find_package(
        Python3
        REQUIRED
        COMPONENTS
            Development
            NumPy
    )

    # Find pybind11 for python bindings to C++
    find_package(
        pybind11
    )
    if (pybind11_FOUND)
        add_definitions(-DHAVE_PYBIND11)
    endif()
endif()

if (WITH_LIBUSB)
    # Find pkg-config
    pkg_check_modules(
        LIBUSB
        libusb-1.0
    )

    # Let the source know that we found libusb
    if (LIBUSB_FOUND)
        add_definitions(-DHAVE_LIBUSB)
    endif()
endif()

# Add the main library
add_subdirectory( src )

# Add the application executables
add_subdirectory( app )

# Export the library for other projects to use
install(
    TARGETS
		"${PROJECT_NAME}"
		"${PROJECT_NAME}Base"
        "${PROJECT_NAME}HwIfc"
    EXPORT "${PROJECT_NAME}Targets"
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Export the target so that it can be imported by other CMake projects
install(
    EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Config.cmake"
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION "lib/cmake/${PROJECT_NAME}"
)

# Optionally, export a package configuration file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

# Install the lexikanConfig and lexikanConfigVersion files
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
        "lib/cmake/${PROJECT_NAME}"
)

install(
    FILES
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.hpp"
    DESTINATION
        "include/${PROJECT_NAME}"
)