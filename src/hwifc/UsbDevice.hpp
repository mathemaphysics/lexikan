#pragma once

// Configuration
#include <lexikanConfig.hpp>

// std
#include <string>
#include <memory>
#include <utility>
#include <cstdint>
#include <cstddef>

// Local
#include <IHasUUID.hpp>

// libusb-1.0
#include <libusb-1.0/libusb.h>

namespace lexikan
{
    class UsbDevice
        : public IHasUUID,
          public std::enable_shared_from_this<UsbDevice>
    {
    public:
        using Ptr = std::shared_ptr<UsbDevice>;
        using ConstPtr = std::shared_ptr<UsbDevice const>;
        using WeakPtr = std::weak_ptr<UsbDevice>;

        static Ptr create(std::uint16_t vendorId_, std::uint16_t deviceId_);
        Ptr getPtr();
        ~UsbDevice();

        int open(libusb_context* context_);
        void close();
    
    private:
        UsbDevice(std::uint16_t vendorId_, std::uint16_t deviceId_);

        std::uint16_t _vendorId;
        std::uint16_t _deviceId;
        libusb_device_handle *_device;
    };
}
