#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
  GLuint createShaderProgram(const std::string &vertPath, const std::string &fragPath);

private:
  GLuint compileShader(GLuint type, const std::string &source);
};
