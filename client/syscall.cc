#include "x-platform/syscall.h"

#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
  const std::string message("Hello message string\n");
  auto result = XPlatform::Syscall::WriteToStdout(message);
  std::cout << "Write result=" << result << std::endl;

  const auto *const message_ptr = "Hello message ptr\n";
  result = XPlatform::Syscall::WriteToStdout(message_ptr);
  std::cout << "Write result=" << result << std::endl;
  return 0;
}
