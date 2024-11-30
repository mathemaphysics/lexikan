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

if (BUILD_PYTHON)
    find_package(
        Python3
        REQUIRED
        COMPONENTS
            Development
            NumPy
    )
endif()

add_subdirectory( src )
add_subdirectory( app )

# Export the library for other projects to use
install(
    TARGETS
		"${PROJECT_NAME}"
		"${PROJECT_NAME}Base"
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