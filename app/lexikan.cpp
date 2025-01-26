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
#include <thread>
#include <chrono>

// src
#include <Base.hpp>
#include <hwifc/UsbDevice.hpp>
#include <hwifc/UsbInterface.hpp>

// Shorthand names
namespace po = boost::program_options;
namespace sp = spdlog;

int main(int argc, char** argv)
{
	// Options examples
	int opt;
	auto logger = sp::stderr_color_st(PROJECT_NAME);

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

	std::uint16_t vendorId = 0x2341;
	std::uint16_t deviceId = 0x0070;

	libusb_init(NULL);

	auto device = libusb_open_device_with_vid_pid(
		NULL,
		vendorId,
		deviceId
	);
	if (!device)
		return -1;

	// If set automatically detach the kernel driver
	libusb_set_auto_detach_kernel_driver(device, 1);
	
	std::cout << "Address of device 1: " << std::hex << device << std::endl;
	auto result = libusb_claim_interface(device, 1);
	if (result < 0)
	{
		std::cout << "Error: " << libusb_error_name(result) << std::endl;
		return -2; 
	}
	std::cout << "Address of device 2: " << std::hex << device << std::endl;

	int bytesTransferred = 64;
	std::cout << "Address of device 3: " << std::hex << device << std::endl;
	auto buffer = new unsigned char[64];
	int numbytes = 64;
	for(int i = 0; i < 10; ++i)
	{
		auto tresult = libusb_interrupt_transfer(
			device,
			0x84,          // The IN endpoint address
			buffer,            // Pointer to a single byte buffer
			numbytes,          // Number of bytes to read
			&bytesTransferred,  // Actual number of bytes transferred
			1000            // Timeout in milliseconds
		);

		if (tresult != 0)
			std::cout << "fail" << std::endl;
		else
		{
			std::cout << "Transferred " << bytesTransferred << " bytes" << std::endl;
			std::cout << std::string(reinterpret_cast<char*>(buffer), bytesTransferred) << std::endl;
		}
	}

	libusb_release_interface(device, 1);
	libusb_close(device);
	libusb_exit(NULL);

	return 0;
}