#pragma once
#include <stdexcept>
#include <string>

namespace linalg {
class DimensionError : public std::invalid_argument {
public:
  explicit DimensionError(const std::string &msg)
      : std::invalid_argument("Dimension Error: " + msg) {}
};

class IndexOutOfBounds : public std::out_of_range {
public:
  explicit IndexOutOfBounds(const std::string &msg)
      : std::out_of_range("Index out of bounds" + msg) {}
};
} // namespace linalg
