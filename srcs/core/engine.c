#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "graphics/mesh.h"
#include "core/window.h"
#include "graphics/shader.h"

static Mesh trimesh;
static Mesh cubemesh;
static GLFWwindow *mwindow;
struct Shader retshader;
void processInput(GLFWwindow *window);


bool eng_init(void) {
  // window init
  mwindow = window_init();
  // cam / shaders
  retshader = shader_init("/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl", "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
float triangle_vertices[] = {
    //   x      y     z     r     g     b
    -0.8f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // bottom left
    -0.4f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
    -0.6f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f   // top
};
float square_vertices[] = {
     0.2f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
     0.8f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,
     0.8f,  0.2f, 0.0f,   0.0f, 1.0f, 1.0f,
     0.2f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
     0.8f,  0.2f, 0.0f,   0.0f, 1.0f, 1.0f,
     0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f
};

 trimesh = mesh_init(triangle_vertices, 3, NULL, 0);
  cubemesh = mesh_init(square_vertices, 6, NULL, 0);
  return true;
}

void eng_run(void) {
  while(!glfwWindowShouldClose(mwindow)){
  processInput(mwindow);
  glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  use_shader(&retshader);
  mesh_draw(&trimesh);
  mesh_draw(&cubemesh);
  glfwSwapBuffers(mwindow);
  glfwPollEvents();
  }
}

void eng_term(void) {
remove_shader(&retshader);
mesh_remove(&trimesh);
mesh_remove(&cubemesh);
glfwTerminate();
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}
