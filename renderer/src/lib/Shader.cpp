#include "File.hpp"
#include "Shader.hpp"

#include "iostream"

GLuint Shader::createShaderProgram(const std::string &vertPath, const std::string &fragPath)
{
  File file;
  GLuint vert = compileShader(GL_VERTEX_SHADER, file.readFile(vertPath));
  GLuint frag = compileShader(GL_FRAGMENT_SHADER, file.readFile(fragPath));

  GLuint program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cerr << "Program error: " << infoLog << std::endl;
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
  return program;
}

GLuint Shader::compileShader(GLuint type, const std::string &source)
{
  GLuint shader = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Shader error: " << infoLog << std::endl;
  }
  return shader;
}