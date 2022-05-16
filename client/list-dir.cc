#include <iostream>
#include <system_error>
#include <variant>

#include "x-platform/dirent.h"

int main(int argc, char *argv[]) {
  XPlatform::Dirent dirent(
      R"(C:\Users\Gautham\projects\github\x-platform\client)");

  for (auto dir_entry = dirent.NextFile();
       !std::holds_alternative<std::monostate>(dir_entry);
       dir_entry = dirent.NextFile()) {
    if (std::holds_alternative<std::error_code>(dir_entry)) {
      const auto err = std::get<std::error_code>(dir_entry);
      std::cerr << "Error in listing directory: " << err.message() << std::endl;
      return 0;
    }

    if (std::holds_alternative<std::filesystem::directory_entry>(dir_entry)) {
      const auto entry = std::get<std::filesystem::directory_entry>(dir_entry);
      std::cout << entry.path().string() << std::endl;
    }
  }

  return 0;
}
