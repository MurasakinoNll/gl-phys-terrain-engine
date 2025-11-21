#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/window.h"
#include <stdbool.h>
#include <stdio.h>
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
GLFWwindow *window_init(void) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(1920, 1080, "garakengine", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  printf("loading glad;");
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return NULL;
    printf("glad load failed");
  }
  return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  (void)window;
}
