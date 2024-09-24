cmake_minimum_required(VERSION 3.20)

# Define the project name and version
project(lexikan VERSION 1.0.0)

option( BUILD_PYTHON "Build the python bindings" ON )
option( BUILD_DOC "Build the documentation" OFF )

find_package(
	Boost
	REQUIRED
	COMPONENTS
		program_options
		system
)

find_package(
	spdlog
	REQUIRED
)

add_subdirectory( src )
add_subdirectory( app )

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
        "${PROJECT_NAME}Config.cmake"
        "${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
        "lib/cmake/${PROJECT_NAME}"
)