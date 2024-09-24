// Logging
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Program options
#include <boost/program_options.hpp>

// std
#include <vector>
#include <string>

// Shorthand names
namespace po = boost::program_options;
namespace sp = spdlog;

int main(int argc, char** argv)
{
	// Options examples
	int opt;

	// Set up the program options
	po::options_description options("Allowed options");
	options.add_options()
		("help", "Outputs this help message")
		("verbose", "Causes us to emit screeches")
		("help", "produce help message")
    	("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
    	("include-path,I", po::value<std::vector<std::string>>(), "include path")
		("input-file", po::value< std::vector<std::string>>(), "input file")
		;
	
	po::variables_map varmap;
	po::store(po::parse_command_line(argc, argv, options), varmap);
	po::notify(varmap);
}