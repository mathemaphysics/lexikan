#include "UsbDevice.hpp"

// std
#include <cstdint>
#include <cstddef>

/**
 * @namespace lexikan
 */
namespace lexikan
{
    UsbDevice::UsbDevice(
        UsbInterface::Ptr usbifc_,
        std::uint16_t vendorId_,
        std::uint16_t deviceId_
    )
        : _usbifc{usbifc_},
          _vendorId{vendorId_},
          _deviceId{deviceId_},
          _device{NULL}
    {
        // Setup the device
    }

    UsbDevice::Ptr UsbDevice::create(
        UsbInterface::Ptr usbifc_,
        std::uint16_t vendorId_,
        std::uint16_t deviceId_
    )
    {
        return Ptr(
            new UsbDevice(
                usbifc_,
                vendorId_,
                deviceId_
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

    int UsbDevice::open()
    {
        auto _device = libusb_open_device_with_vid_pid(
            _usbifc->getContext(),
            _vendorId,
            _deviceId
        );
        if (!_device)
            return -1;
        else
            return 0;
    }

    int UsbDevice::read()
    {

    }

    void UsbDevice::close()
    {
        if (_device)
        {
            libusb_close(_device);
            _device = NULL;
        }
    }
}
