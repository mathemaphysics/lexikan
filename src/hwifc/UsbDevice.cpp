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
        int interfaceId_
    )
        : _usbifc{usbifc_},
          _vendorId{vendorId_},
          _deviceId{deviceId_},
          _device{NULL},
          _interfaceId{interfaceId_}
    {
        // Setup the device
    }

    UsbDevice::Ptr UsbDevice::create(
        UsbInterface::Ptr usbifc_,
        std::uint16_t vendorId_,
        std::uint16_t deviceId_,
        int interfaceId_
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

        std::cout << "Address of device: " << std::hex << _device << std::endl;
        auto result = libusb_claim_interface(_device, _interfaceId);
        if (result < 0)
        {
            this->close();
            std::cout << "Error: " << libusb_error_name(result) << std::endl;
            return -2; 
        }

        return 0;
    }

    int UsbDevice::read(unsigned char endpoint_, unsigned char* buffer_, int numbytes_, unsigned int timeout_)
    {
        int bytesTransferred = 0;
        auto result = libusb_bulk_transfer(
            _device,
            endpoint_,          // The IN endpoint address
            buffer_,            // Pointer to a single byte buffer
            numbytes_,          // Number of bytes to read
            &bytesTransferred,  // Actual number of bytes transferred
            timeout_            // Timeout in milliseconds
        );

        return result;
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
