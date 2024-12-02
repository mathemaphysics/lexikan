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
#include "../src/Base.hpp"

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

	logger->info("Welcome to lexikan!");

	lexikan::Base x;
	logger->info("Object UUID: {}", lexikan::IHasUUID::toString(x.getUUID()));

	return 0;
}