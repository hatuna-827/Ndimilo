#include "File.hpp"

std::string File::readFile(const std::string &filename)
{
  std::ifstream file("../src/" + filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

json File::readJson(const std::string &filename)
{
  std::ifstream file("../src/" + filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open file: " + filename);
  }
  json data;
  file >> data;
  return data;
}
