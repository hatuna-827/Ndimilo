#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class File
{
public:
  std::string readFile(const std::string &filename);
  json readJson(const std::string &filename);
};
