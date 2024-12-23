#include "UsbDevice.hpp"

// std
#include <cstdint>
#include <cstddef>

/**
 * @namespace lexikan
 */
namespace lexikan
{
    UsbDevice::UsbDevice(std::uint16_t vendorId_, std::uint16_t deviceId_)
        : _vendorId{vendorId_},
          _deviceId{deviceId_},
          _device{NULL}
    {
        // Setup the device
    }

    UsbDevice::Ptr UsbDevice::create(std::uint16_t vendorId_, std::uint16_t deviceId_)
    {
        return Ptr(new UsbDevice(vendorId_, deviceId_));
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

    int UsbDevice::open(libusb_context* context_)
    {
        auto _device = libusb_open_device_with_vid_pid(context_, _vendorId, _deviceId);
        if (!_device)
            return -1;
        else
            return 0;
    }

    void UsbDevice::close()
    {
        libusb_close(_device);
    }
}
