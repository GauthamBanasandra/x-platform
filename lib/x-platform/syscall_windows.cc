/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
