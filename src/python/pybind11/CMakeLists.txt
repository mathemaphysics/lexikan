add_library(
    testmod
    SHARED
        testmodPybind.cpp
)

target_link_libraries(
    testmod
    PUBLIC
        pybind11::module
)

set_target_properties(
    testmod
    PROPERTIES
        PREFIX ""
)

install(
    TARGETS
        testmod
    ARCHIVE DESTINATION lib/python
    LIBRARY DESTINATION lib/python
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
