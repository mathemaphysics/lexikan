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

    UsbInterface::~UsbInterface()
    {

    }
    
    std::vector<libusb_device*> UsbInterface::getDeviceList()
    {
        // Get a list of USB devices
        auto count = libusb_get_device_list(_context, &_devices);
        _deviceList.resize(count);
        _deviceList.assign(count, *_devices);

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