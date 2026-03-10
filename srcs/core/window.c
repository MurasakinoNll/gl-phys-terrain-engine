#include <glad/glad.h>
#include "core/window.h"
#include "graphics/camera.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
GLFWwindow *window_init(void) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  GLFWwindow *window = glfwCreateWindow(960, 540, "garakengine", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  printf("loading glad;");
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return NULL;
    fprintf(stderr, "glad load failed");
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetCursorPosCallback(window, mouse_callback);

  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
printf("Renderer: %s\n", glGetString(GL_RENDERER));
printf("Version:  %s\n", glGetString(GL_VERSION));
  return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  (void)window;
}
void mouse_callback(GLFWwindow *window, double xpos, double ypos){
  static float lastX = 480, lastY = 260;
  static bool firstMouse = true;
  if (firstMouse){
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
    return;
  }
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX=xpos; lastY=ypos;
  const float sens = 0.1f;
  xoffset *=sens;
  yoffset *=sens;
  Edirection.yaw += xoffset;
  Edirection.pitch += yoffset;
  if (Edirection.pitch > 89.0f) {Edirection.pitch = 89.0f;}
  if (Edirection.pitch < -89.0f) {Edirection.pitch = -89.0f;}
}
