#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

std::string GetDesc() {
  std::stringstream desc;
  desc << "Usage: hdfs_allowSnapshot [OPTION] PATH" << std::endl
       << std::endl
       << "Allowing snapshots of a directory at PATH to be created."
       << std::endl
       << "If the operation completes successfully, the directory becomes "
          "snapshottable."
       << std::endl
       << std::endl
       << "  -h        display this help and exit" << std::endl
       << std::endl
       << "Examples:" << std::endl
       << "hdfs_allowSnapshot hdfs://localhost.localdomain:8020/dir"
       << std::endl
       << "hdfs_allowSnapshot /dir1/dir2" << std::endl;
  return desc.str();
}

int main(int argc, char *argv[]) {
  // We should have at least 2 arguments
  if (argc < 2) {
    std::cout << GetDesc();
    exit(EXIT_FAILURE);
  }

  po::options_description desc("hdfs_allowSnapshot");
  desc.add_options()("help,h", "Show the help for hdfs_allowSnapshot")(
      "path", po::value<std::string>(),
      "The path to the directory to make it snapshot-able");

  po::positional_options_description pos_desc;
  pos_desc.add("path", 1);

  po::variables_map var_map;
  po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(pos_desc)
                .run(),
            var_map);
  po::notify(var_map);

  if (var_map.count("help") > 0) {
    std::cout << GetDesc();
    return 0;
  }

  if (var_map.count("path") > 0) {
    const auto path = var_map["path"].as<std::string>();
    std::cout << "Allowing snapshot for the path: " << path << std::endl;
    return 0;
  }

  return 0;
}
