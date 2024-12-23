set (
    target
        "${PROJECT_NAME}HwIfc"
)

set (
    sources
        $<$<BOOL:${WITH_LIBUSB}>:UsbInterface.cpp>
        $<$<BOOL:${WITH_LIBUSB}>:UsbDevice.cpp>
)

set (
    headers
        $<$<BOOL:${WITH_LIBUSB}>:UsbInterface.hpp>
        $<$<BOOL:${WITH_LIBUSB}>:UsbDevice.hpp>
)

add_library(
    ${target}
    SHARED
        ${sources}
        ${headers}
)

target_link_libraries(
    ${target}
        "${PROJECT_NAME}Base"
)

target_include_directories(
    ${target}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hwifc>
)

# Specify the properties for the library
set_target_properties(
    "${PROJECT_NAME}HwIfc"
    PROPERTIES
        VERSION
            ${PROJECT_VERSION}
        SOVERSION
            1
        EXPORT_NAME
            "${PROJECT_NAME}Base"
)