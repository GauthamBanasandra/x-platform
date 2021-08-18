#include <filesystem>
#include <iostream>
#include <system_error>

int main(int argc, char *argv[]) {
  const auto temp_dir_path = std::filesystem::temp_directory_path();
  const auto temp_dirs = temp_dir_path / "a/b/c";
  create_directories(temp_dirs);
  std::cout << "Created temp dirs: " << temp_dirs << std::endl;

  std::error_code rmdir_err;
  const auto del_result = remove_all(temp_dirs, rmdir_err);
  std::cerr << "Deleted temp dir: " << temp_dirs << " result: " << del_result
            << " error(if any): " << rmdir_err.message() << std::endl;
  return 0;
}
