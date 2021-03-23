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

  pattern = "?.z.x";
  str = "1.z.x";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "*.doc";
  str = "some/path/abcd.doc";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "*.doc";
  str = R"(some\path\abcd.doc)";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "x*.doc";
  str = "y/abcd.doc";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;

  pattern = "x*.doc";
  str = R"(y\abcd.doc)";
  std::cout << "(" << pattern << ", " << str
            << ") = " << XPlatform::Syscall::FnMatch(pattern, str) << std::endl;
  return 0;
}
