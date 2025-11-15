#include <glad/glad.h>
#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/textures.h"
#include <stdbool.h>
static Mesh cubemesh;
static GLFWwindow *mwindow;
struct Shader retshader;
void processInput(GLFWwindow *window);
bool eng_init(void) {
  mwindow = window_init();
  retshader = shader_init(
      "/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl",
      "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
   float square_vertices[] = {
    //  x     y      z      r    g    b    s    t
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top-left
};
unsigned int square_indices[] = {
    0, 1, 2,  // first triangle (bottom-left, bottom-right, top-right)
    2, 3, 0   // second triangle (top-right, top-left, bottom-left)
  };

   cubemesh = mesh_init(square_vertices, 4, square_indices, 6);

  return true;
}

void eng_run(void) {
int catotex = texture_load("/home/haraku/harakdev/physics-engine-clang/catonew.jpg");
  while (!glfwWindowShouldClose(mwindow)) {
    processInput(mwindow);
    glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    use_shader(&retshader);
    glBindTexture(GL_TEXTURE_2D, catotex);
    glUniform1i(glGetUniformLocation(retshader.id, "objTex"), 0);
     mesh_draw(&cubemesh);
    glfwSwapBuffers(mwindow);
    glfwPollEvents();
  }
}

void eng_term(void) {
  remove_shader(&retshader);
   mesh_remove(&cubemesh);
  glfwTerminate();
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

// testable stuff
// float timeVal = glfwGetTime();
    /*float rgbv = (sinf(timeVal) / 2.0f) + 0.5f;
    float rgbc = (cosf(timeVal)*2)+0.3f;
    float rgba = (1/ (sinf(timeVal*3))+0.1f);
    int vertColorLoc = glGetUniformLocation(retshader.id, "mainColor");
    glUseProgram(retshader.id);
    glUniform4f(vertColorLoc, rgba, rgbv, rgbc, 0.0f);*/
