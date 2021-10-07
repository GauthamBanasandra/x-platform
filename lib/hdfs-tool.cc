#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>

#include "hdfs-tool.h"

bool HdfsTool::Do() {
  if (!InitializeOptions()) {
    std::cerr << "Unable to initialize the options" << std::endl;
    return false;
  }

  if (!ValidateConstraints()) {
    std::cout << GetDescription() << std::endl;
    return false;
  }
}
