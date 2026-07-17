#include "lib/File.hpp"
#include "lib/Shader.hpp"

#include <nlohmann/json.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using json = nlohmann::json;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

int main()
{
  File file;
  Shader shader;

  // GLFWの初期化
  if (!glfwInit())
  {
    return -1;
  }

  // Windowの作成
  GLFWwindow *window = glfwCreateWindow(800, 600, "Ndimilo Renderer", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // OpenGLコンテキストを現在のスレッドに設定
  glfwMakeContextCurrent(window);

  // GLADでOpenGL関数をロード
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    return -1;
  }

  // コールバックの登録
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  // シェーダーの作成
  GLuint program = shader.createShaderProgram("shaders/vertex.vert", "shaders/fragment.frag");

  // VBO,VAOの作成
  float vertices[] = {
      -0.5f,
      -0.5f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      0.5f,
      -0.5f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      0.5f,
      0.0f,
      0.0f,
      0.0f,
      1.0f,
  };
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
      0, 3,
      GL_FLOAT, GL_FALSE,
      6 * sizeof(float),
      (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
      1, 3,
      GL_FLOAT, GL_FALSE,
      6 * sizeof(float),
      (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window))
  {
    // 背景色をクリア
    glClearColor(.9f, .9f, .9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // ダブルバッファリング：描画バッファを交換
    glfwSwapBuffers(window);
    // イベントを処理
    glfwPollEvents();
  }

  // VAO,VBO,シェーダーの削除
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(program);

  // 終了処理
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}