set (target PyLexikan)

set (
    sources
        basic.cpp
)

set (
    headers
)

set (
    libs
        Python3::Module
        Python3::NumPy
)

add_library(${target} SHARED ${sources} ${headers})
target_link_libraries(${target} ${libs})
set_target_properties(${target} PROPERTIES PREFIX "")
