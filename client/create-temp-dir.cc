#include <cerrno>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "x-platform/syscall.h"

int main(int argc, char *argv[]) {
  std::string tmp_dir_name("test_XXXXXX");
  std::vector<char> tmp_dir_pattern(tmp_dir_name.begin(), tmp_dir_name.end());

  if (!XPlatform::Syscall::CreateTempDir(tmp_dir_pattern)) {
    std::cout << "Failed to create folder: " << std::strerror(errno)
              << std::endl;
    tmp_dir_name.assign(tmp_dir_pattern.data());
    std::cout << "Temp dir path: " << tmp_dir_name << std::endl;
    return 0;
  }
}
