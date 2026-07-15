#include "lib/File.hpp"

#include <nlohmann/json.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

int main()
{
  File file;

  if (!glfwInit())
  {
    return -1;
  }

  GLFWwindow *window =
      glfwCreateWindow(
          800,
          600,
          "Ndimilo Renderer",
          nullptr,
          nullptr);

  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    return -1;
  }

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  std::string vertexSource = file.readFile("shaders/vertex.glsl");
  const char *shaderSrc = vertexSource.c_str();
  glShaderSource(
      vertexShader,
      1,
      &shaderSrc,
      nullptr);
  glCompileShader(vertexShader);
  GLint success;
  glGetShaderiv(
      vertexShader,
      GL_COMPILE_STATUS,
      &success);
  if (success == GL_FALSE)
  {
    char infoLog[512];
    glGetShaderInfoLog(
        vertexShader,
        512,
        nullptr,
        infoLog);
    std::cout << infoLog << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragmentSource = file.readFile("shaders/fragment.glsl");
  const char *fragmentSrc = fragmentSource.c_str();
  glShaderSource(
      fragmentShader,
      1,
      &fragmentSrc,
      nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(
      fragmentShader,
      GL_COMPILE_STATUS,
      &success);
  if (success == GL_FALSE)
  {
    char infoLog[512];
    glGetShaderInfoLog(
        fragmentShader,
        512,
        nullptr,
        infoLog);
    std::cout << infoLog << std::endl;
  }

  GLuint program = glCreateProgram();
  glAttachShader(
      program,
      vertexShader);
  glAttachShader(
      program,
      fragmentShader);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE)
  {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cout << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
      -0.5f, -0.5f,
      0.5f, -0.5f,
      0.0f, 0.5f};
  GLuint VAO;
  GLuint VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(vertices),
      vertices,
      GL_STATIC_DRAW);
  glVertexAttribPointer(
      0, 2,
      GL_FLOAT, GL_FALSE,
      2 * sizeof(float),
      (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(program);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}