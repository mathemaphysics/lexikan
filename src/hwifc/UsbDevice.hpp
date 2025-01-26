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
#include <hwifc/UsbInterface.hpp>

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

        static Ptr create(
            UsbInterface::Ptr usbifc_,
            std::uint16_t vendorId_ = 0x0000,
            std::uint16_t deviceId_= 0x0000,
            int interfaceId_ = 0,
            bool autoDetachKernel_ = true
        );
        Ptr getPtr();
        ~UsbDevice();

        int open(
            unsigned char endpoint_ = 0x0,
            unsigned char* buffer_ = nullptr,
            int numbytes_ = 1,
            unsigned int timeout_ = 1000
        );
        void close();
     
    //private:
        UsbDevice(
            UsbInterface::Ptr usbifc_,
            std::uint16_t vendorId_ = 0x0000,
            std::uint16_t deviceId_= 0x0000,
            int interfaceId_ = 0,
            bool autoDetachKernel_ = true
        );

        UsbInterface::Ptr _usbifc;
        std::uint16_t _vendorId;
        std::uint16_t _deviceId;
        libusb_device_handle *_device;
        int _interfaceId;
        bool _autoDetachKernel;
    };
}
