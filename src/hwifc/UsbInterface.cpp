#include "UsbInterface.hpp"
#include "UsbDevice.hpp"

// std
#include <cstdint>
#include <cstddef>

namespace lexikan
{
    UsbInterface::UsbInterface()
        : _context{NULL},
          _devices{NULL}
    {

    }

    UsbInterface::Ptr UsbInterface::create()
    {
        return Ptr(new UsbInterface());
    }

    UsbInterface::Ptr UsbInterface::getPtr()
    {
        return shared_from_this();
    }

    UsbInterface::~UsbInterface()
    {

    }
    
    std::vector<libusb_device_descriptor> UsbInterface::getDeviceList()
    {
        // Get a list of USB devices
        auto count = libusb_get_device_list(_context, &_devices);
        _deviceList.resize(count);

        // Get the device descriptor
        for(std::size_t devIdx = 0; devIdx < count; ++devIdx)
        {
            auto& desc = _deviceList.emplace_back();
            int rc = libusb_get_device_descriptor(_devices[devIdx], &desc);
            if (rc < 0)
            {
                fprintf(stderr, "Failed to get device descriptor: %s\n", libusb_error_name(rc));
                continue;
            }
        }

        return _deviceList;
    }

    int UsbInterface::initialize()
    {
        auto rc = libusb_init(&_context);
        if (rc < 0)
            return -1;
        else
            return 0;
    }

    void UsbInterface::finalize()
    {
        libusb_exit(_context);
    }
}