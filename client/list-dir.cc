#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <system_error>
#include <variant>
#include <vector>

#include "x-platform/dirent.h"
#include "x-platform/syscall.h"

void ListDir(const std::string &path);
std::string CreateTempDirsAndFiles(int count);
std::string CreateTempDir(const std::string &pattern = "test_XXXXXX");

int main(int argc, char *argv[]) {
  const auto root = CreateTempDirsAndFiles(20);
  std::cout << "Root: " << root << std::endl;
  std::cout << "Children:" << std::endl;
  ListDir(root);

  std::error_code err;
  std::filesystem::remove_all(root, err);
  if (err) {
    std::cerr << "Unable to delete the root folder " << root
              << " reason: " << err.message() << std::endl;
    return 1;
  }
  return 0;
}

void CreateAndListDir() {}

std::string CreateTempDirsAndFiles(const int count) {
  const auto tmp_dir_path =
      std::filesystem::temp_directory_path() / CreateTempDir();

  for (int i = 0; i < count; ++i) {
    const auto tmp_dir_absolute_path = tmp_dir_path / std::to_string(i);

    if (std::error_code err;
        !std::filesystem::create_directories(tmp_dir_absolute_path, err)) {
      std::cerr << "Unable to create the temp dir "
                << tmp_dir_absolute_path.string()
                << " reason: " << err.message() << std::endl;
      assert(false);
    }

    std::stringstream tmp_filename;
    tmp_filename << i << ".txt";
    std::ofstream{tmp_dir_path / tmp_filename.str()};
  }

  return tmp_dir_path.string();
}

std::string CreateTempDir(const std::string &pattern) {
  std::vector pattern_raw(pattern.begin(), pattern.end());
  if (!XPlatform::Syscall::CreateTempDir(pattern_raw)) {
    std::cerr << "Error in creating temp dir" << std::endl;
    assert(false);
  }

  std::string temp_dir_path(pattern_raw.data());
  std::filesystem::remove(temp_dir_path);
  return temp_dir_path;
}

void ListDir(const std::string &path) {
  XPlatform::Dirent dirent(path);

  for (auto dir_entry = dirent.NextFile();
       !std::holds_alternative<std::monostate>(dir_entry);
       dir_entry = dirent.NextFile()) {
    if (std::holds_alternative<std::error_code>(dir_entry)) {
      const auto err = std::get<std::error_code>(dir_entry);
      std::cerr << "Error in listing directory: " << err.message() << std::endl;
      return;
    }

    if (std::holds_alternative<std::filesystem::directory_entry>(dir_entry)) {
      const auto entry = std::get<std::filesystem::directory_entry>(dir_entry);
      std::cout << entry.path().string() << std::endl;
    }
  }
}