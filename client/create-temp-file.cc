#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "x-platform/syscall.h"

void StringAndVector() {
  std::string tmp_file_name("test_XXXXXXXXXX");
  std::vector<char> tmp_file_name_buf(tmp_file_name.begin(),
                                      tmp_file_name.end());

  const auto fd = XPlatform::Syscall::CreateAndOpenTempFile(tmp_file_name_buf);
  tmp_file_name.assign(tmp_file_name_buf.data());

  if (!XPlatform::Syscall::CloseFile(fd)) {
    std::cout << "Unable to close the file" << std::endl;
  }
}

void CharPtrAndVector() {
  char tmp_file[14] = "stress_XXXXXX";
  std::vector<char> tmp_file_buf(tmp_file, tmp_file + sizeof tmp_file);

  const auto fd = XPlatform::Syscall::CreateAndOpenTempFile(tmp_file_buf);
  if (fd != -1) {
    std::copy_n(tmp_file_buf.begin(), sizeof tmp_file, tmp_file);
  }

  if (!XPlatform::Syscall::CloseFile(fd)) {
    std::cout << "Unable to close the file" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  StringAndVector();
  CharPtrAndVector();
  return 0;
}
