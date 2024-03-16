#pragma once

#include <string>
#include <string_view>

namespace file {
std::string LoadSourceFromFile(std::string_view path);
}