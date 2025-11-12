#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "core/window.h"
#include "graphics/shader.h"
static GLFWwindow *mwindow;
struct Shader retshader;
void processInput(GLFWwindow *window);
bool eng_init(void) {
  // window init
  mwindow = window_init();
  // cam / shaders
  retshader = shader_init("/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl", "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
  return true;
}

void eng_run(void) {
  while(!glfwWindowShouldClose(mwindow)){
  processInput(mwindow);
  glClearColor(1.0f, 1.0f, 1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  use_shader(&retshader);
    //renderer+draw, uniforms, bind, rigids

  glfwSwapBuffers(mwindow);
   glfwPollEvents();
  }
}

void eng_term(void) {
remove_shader(&retshader);
glfwTerminate();
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}
