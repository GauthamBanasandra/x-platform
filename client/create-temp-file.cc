#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "x-platform/syscall.h"

int main(int argc, char *argv[]) {
  std::string tmp_file_name("xyz_XXXXXX");
  std::vector<char> tmp_file_name_buf(tmp_file_name.begin(),
                                      tmp_file_name.end());
  tmp_file_name_buf.resize(tmp_file_name_buf.size() + 1);

  const auto fd = XPlatform::Syscall::CreateTempFile(tmp_file_name_buf);
  if (!XPlatform::Syscall::CloseFile(fd)) {
    std::cout << "Unable to close the file" << std::endl;
  }

  return 0;
}
