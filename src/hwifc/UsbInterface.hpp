#pragma once

// Configuration
#include <lexikanConfig.hpp>

// std
#include <string>
#include <memory>
#include <utility>
#include <cstdint>
#include <cstddef>
#include <vector>

// Local
#include <IHasUUID.hpp>

// libusb-1.0
#include <libusb-1.0/libusb.h>

namespace lexikan
{
    class UsbInterface
        : public IHasUUID,
          public std::enable_shared_from_this<UsbInterface>
    {
    public:
        using Ptr = std::shared_ptr<UsbInterface>;
        using ConstPtr = std::shared_ptr<UsbInterface const>;
        using WeakPtr = std::weak_ptr<UsbInterface>;

        static Ptr create();
        Ptr getPtr();
        ~UsbInterface();

        std::vector<libusb_device_descriptor>& getDeviceList();

        libusb_context* getContext();

    private:
        UsbInterface();

        // Methods
        int initialize();
        void finalize();
        int openDevice(std::uint16_t vendorId_, std::uint16_t deviceId_);
    
        // Members
        libusb_context *_context;
        libusb_device **_devices;
        std::vector<libusb_device_descriptor> _deviceList;
    };
}