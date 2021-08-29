#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include "options.h"

namespace po = boost::program_options;

class HdfsAllowSnapshot {
public:
  HdfsAllowSnapshot(int argc, char **argv);

  [[nodiscard]] bool ValidateConstraints() const { return argc_ > 1; }
  static std::string GetDescription();

  [[nodiscard]] bool Do() const;

protected:
  struct OptionsHandlers {
    static void HandleHelp();
    static void HandlePath(const std::string &path);
  };

private:
  int argc_;
  po::variables_map opt_val_;
  po::options_description opt_desc_;
  po::positional_options_description pos_opt_desc_;
};

HdfsAllowSnapshot::HdfsAllowSnapshot(const int argc, char **argv)
    : argc_{argc}, opt_desc_{"hdfs_allowSnapshot"} {
  opt_desc_.add_options()("help,h", "Show the help for hdfs_allowSnapshot")(
      "path", po::value<std::string>(),
      "The path to the directory to make it snapshot-able");

  pos_opt_desc_.add("path", 1);

  po::store(po::command_line_parser(argc, argv)
                .options(opt_desc_)
                .positional(pos_opt_desc_)
                .run(),
            opt_val_);
  po::notify(opt_val_);
}

std::string HdfsAllowSnapshot::GetDescription() {
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

bool HdfsAllowSnapshot::Do() const {
  if (!ValidateConstraints()) {
    std::cout << GetDescription();
    return false;
  }

  if (opt_val_.count("help") > 0) {
    OptionsHandlers::HandleHelp();
    return true;
  }

  if (opt_val_.count("path") > 0) {
    const auto path = opt_val_["path"].as<std::string>();
    OptionsHandlers::HandlePath(path);
    return true;
  }

  return true;
}

void HdfsAllowSnapshot::OptionsHandlers::HandleHelp() {
  std::cout << GetDescription();
}

void HdfsAllowSnapshot::OptionsHandlers::HandlePath(const std::string &path) {
  std::cout << "Allowing snapshot for the path: " << path << std::endl;
}

int main(int argc, char *argv[]) {
  const HdfsAllowSnapshot allow_snapshot(argc, argv);
  if (!allow_snapshot.Do()) {
    exit(EXIT_FAILURE);
  }
  return 0;
}
