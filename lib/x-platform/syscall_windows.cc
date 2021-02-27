#include "syscall.h"

#include <Windows.h>

bool XPlatform::Syscall::WriteToStdout(const std::string &message) {
  auto *const stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (stdout_handle == INVALID_HANDLE_VALUE || stdout_handle == nullptr) {
    return false;
  }

  unsigned long bytes_written = 0;
  const auto *const msg_ptr = message.c_str();
  const auto result = WriteFile(stdout_handle, msg_ptr, lstrlen(msg_ptr),
                                &bytes_written, nullptr);
  return result && message.length() == bytes_written;
}
