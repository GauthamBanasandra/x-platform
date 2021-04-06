#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

#include "x-platform/syscall.h"

int main(int argc, char *argv[]) {
  std::vector<char> numbers(20);
  std::iota(numbers.begin(), numbers.end(), 'a');

  for (const auto number : numbers) {
    std::cout << number << ' ';
  }
  std::cout << std::endl;

  XPlatform::Syscall::ClearBufferSafely(numbers.data(), numbers.size());
  for (const auto number : numbers) {
    std::cout << static_cast<int>(number) << ' ';
  }
  std::cout << std::endl;
  return 0;
}
