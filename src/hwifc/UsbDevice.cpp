#include "UsbDevice.hpp"

// std
#include <cstdint>
#include <cstddef>
#include <iostream>

/**
 * @namespace lexikan
 */
namespace lexikan
{
    UsbDevice::UsbDevice(
        UsbInterface::Ptr usbifc_,
        std::uint16_t vendorId_,
        std::uint16_t deviceId_,
        int interfaceId_,
        bool autoDetachKernel_
    )
        : _usbifc{usbifc_},
          _vendorId{vendorId_},
          _deviceId{deviceId_},
          _device{NULL},
          _interfaceId{interfaceId_},
          _autoDetachKernel{autoDetachKernel_}
    {
        // Setup the device
    }

    UsbDevice::Ptr UsbDevice::create(
        UsbInterface::Ptr usbifc_,
        std::uint16_t vendorId_,
        std::uint16_t deviceId_,
        int interfaceId_,
        bool autoDetachKernel_
    )
    {
        return Ptr(
            new UsbDevice(
                usbifc_,
                vendorId_,
                deviceId_,
                interfaceId_,
                autoDetachKernel_
            )
        );
    }

    UsbDevice::Ptr UsbDevice::getPtr()
    {
        return shared_from_this();
    }

    UsbDevice::~UsbDevice()
    {
        // Tear down the device
        close();
    }

    int UsbDevice::open(
        unsigned char endpoint_,
        unsigned char* buffer_,
        int numbytes_,
        unsigned int timeout_
    )
    {
        return 0;
    }

    void UsbDevice::close()
    {
        if (_device)
        {
            libusb_release_interface(_device, _interfaceId);
            libusb_close(_device);
            //_device = NULL;
        }
    }
}
