#include <iostream>
#include <ostream>
#include <string>

#include "x-platform/syscall.h"

int main(int argc, char *argv[]) {
  std::string pattern("a*.doc");
  std::string str("abcd.doc");
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "*";
  str = "x";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "*.z.x";
  str = "/a.z.x";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "*.z.x";
  str = "z.x";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;
  return 0;
}
