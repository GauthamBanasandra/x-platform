#include <iostream>
#include <ostream>

#include "x-platform/syscall.h"

int main(int argc, char *argv[]) {
  std::cout << XPlatform::Syscall::StringCompareIgnoreCase("aBcDeF", "AbCdEf")
            << std::endl;
  std::cout << XPlatform::Syscall::StringCompareIgnoreCase("", "") << std::endl;
  std::cout << XPlatform::Syscall::StringCompareIgnoreCase("12345", "abcde")
            << std::endl;
  return 0;
}
