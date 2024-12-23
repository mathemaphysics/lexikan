// Configuration
#include <lexikanConfig.hpp>

// Logging
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// jsoncpp
#ifdef WITH_JSONCPP
#include <json/json.h>
#endif

// Program options
#include <boost/program_options.hpp>

// std
#include <vector>
#include <string>
#include <iostream>

// src
#include <Base.hpp>
#include <hwifc/UsbDevice.hpp>

// libusb
#include <libusb-1.0/libusb.h>

// Shorthand names
namespace po = boost::program_options;
namespace sp = spdlog;

int main(int argc, char** argv)
{
	// Options examples
	int opt;
	auto logger = sp::stderr_color_mt(PROJECT_NAME);

	// Set up the program options
	po::options_description options("Allowed options");
	options.add_options()
		("help", "Outputs this help message")
		("verbose", "Causes us to emit screeches")
		("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
		("include-path,I", po::value<std::vector<std::string>>(), "include path")
		("input-file", po::value< std::vector<std::string>>(), "input file")
		;
	
	po::variables_map varmap;
	try
	{
		po::store(po::parse_command_line(argc, argv, options), varmap);
		po::notify(varmap);
	}
	catch (po::unknown_option& ex)
	{
		logger->error("Unknown option: {}", ex.what());
		options.print(std::cerr);
	}
	catch (po::invalid_option_value& ex)
	{
		logger->error("Bad option: {}", ex.what());
		options.print(std::cerr);
	}
	catch (po::error_with_option_name& ex)
	{
		logger->error("Option error: {}", ex.what());
		options.print(std::cerr);
	}
	catch (...)
	{
		logger->error("Unknown exception caught");
	}

	logger->info("Welcome to lexikan!");

    libusb_context *ctx = NULL;
    int rc = libusb_init(&ctx);
    if (rc < 0) {
        fprintf(stderr, "Failed to init libusb\n");
        return 1;
    }

	libusb_device_handle *handle = libusb_open_device_with_vid_pid(ctx, 0x239a, 0x802b);
	if (!handle) {
		fprintf(stderr, "Cannot open device\n");
		return 1;
	}

    // Get a list of USB devices
    libusb_device **dev_list = NULL;
    auto count = libusb_get_device_list(ctx, &dev_list);
    if (count < 0) {
        fprintf(stderr, "Failed to get USB device list: %s\n", libusb_error_name((int)count));
        libusb_exit(ctx);
        return 1;
    }

    printf("Found %zd USB devices:\n", count);

    // Iterate over all devices
    for (std::size_t i = 0; i < count; i++) {
        libusb_device *device = dev_list[i];
        struct libusb_device_descriptor desc;

        // Get the device descriptor
        rc = libusb_get_device_descriptor(device, &desc);
        if (rc < 0) {
            fprintf(stderr, "Failed to get device descriptor: %s\n", libusb_error_name(rc));
            continue;
        }

        // Print some basic info
        printf("  Device %zu: VendorID=%04x, ProductID=%04x, Class=%02x, Subclass=%02x, Protocol=%02x\n",
               i, desc.idVendor, desc.idProduct,
               desc.bDeviceClass, desc.bDeviceSubClass, desc.bDeviceProtocol);
    }

    // Free the device list
    libusb_free_device_list(dev_list, 1);

    libusb_exit(ctx);

	return 0;
}