#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "graphics/mesh.h"
#include "core/window.h"
#include "graphics/shader.h"

static Mesh tetra;
static GLFWwindow *mwindow;
struct Shader retshader;
void processInput(GLFWwindow *window);


bool eng_init(void) {
  // window init
  mwindow = window_init();
  // cam / shaders
  retshader = shader_init("/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl", "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
  float vertices[] = {
        // positions        // colors
         1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f
    };
    unsigned int indices[] = {
        0,1,2, 0,1,3, 0,2,3, 1,2,3
    };
  tetra = mesh_init(vertices, 4, indices, 12);
  return true;
}

void eng_run(void) {
  while(!glfwWindowShouldClose(mwindow)){
  processInput(mwindow);
  glClearColor(0.0f, 0.0f, 0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  use_shader(&retshader);
    mesh_draw(&tetra);
    //renderer+draw, uniforms, bind, rigids
  
  glfwSwapBuffers(mwindow);
   glfwPollEvents();
  }
}

void eng_term(void) {
remove_shader(&retshader);
mesh_remove(&tetra);
glfwTerminate();
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}
