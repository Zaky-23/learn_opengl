#include "file.hpp"

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#include "log.hpp"

namespace file {
std::string LoadSourceFromFile(std::string_view path) {
  std::ifstream file(path.data());

  if (!file.is_open()) {
    LOG_CRITICAL("{}: Failed to open file", path);
    if (file.bad()) {
      LOG_CRITICAL("{}: Bad Bit", path);
    }
    if (file.fail()) {
      LOG_CRITICAL("{}: Fail Bit", path);
    }
    if(file.eof()) {
      LOG_CRITICAL("{}: Eof Bit", path);
    }
    LOG_CRITICAL("{}: {} byte(s) read", path, file.gcount());

    return {};
  }

  std::stringstream buffer;
  
  buffer << file.rdbuf();

  std::string result = buffer.str();

  file.close();

  return result;
}
}