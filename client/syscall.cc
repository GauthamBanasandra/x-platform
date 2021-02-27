#include "x-platform/syscall.h"

#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  const auto result = XPlatform::Syscall::WriteToStdout("Hello message\n");
  std::cout << "Write result=" << result << std::endl;
  return 0;
}
