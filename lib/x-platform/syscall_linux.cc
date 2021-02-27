#include "syscall.h"

#include <unistd.h>

bool XPlatform::Syscall::WriteToStdout(const std::string &message) {
  const auto result = write(1, message.c_str(), message.length());
  return result == static_cast<ssize_t>(message.length());
}
