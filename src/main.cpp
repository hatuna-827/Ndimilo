#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
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

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0, .3, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}