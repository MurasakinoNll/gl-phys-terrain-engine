#include <cglm/affine.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <glad/glad.h>
#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/textures.h"
#include "core/time.h"
#include <stdbool.h>
#include <cglm/cglm.h>
#include <stdio.h>
static Mesh cubemesh;
static GLFWwindow *mwindow;
struct Shader retshader;
void processInput(GLFWwindow *window);
bool eng_init(void) {
  mwindow = window_init();
  
  retshader = shader_init(
      "/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl",
      "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
float cubeVertices[] = {
    //   X           Y           Z        R      G       B              S        T   
    -0.5f, -0.5f,  0.5f,   1, 0, 0,       0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0, 1, 0,       1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0, 0, 1,       1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0, 0, 1,       1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   1, 1, 0,       0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   1, 0, 0,       0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   1, 0, 1,       1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0, 1, 1,       0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1, 1, 1,       0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1, 1, 1,       0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   0, 0, 0,       1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   1, 0, 1,       1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1, 1, 1,       1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1, 0, 1,       0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0, 1, 1,       0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0, 1, 1,       0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   1, 0, 0,       1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1, 1, 1,       1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0, 1, 0,       0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1, 1, 0,       1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1, 0, 1,       1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1, 0, 1,       1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0, 0, 1,       0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0, 1, 0,       0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1, 1, 1,       0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1, 1, 0,       1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1, 0, 0,       1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1, 0, 0,       1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0, 1, 0,       0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   1, 1, 1,       0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0, 0, 0,       1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1, 0, 0,       0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0, 1, 0,       0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0, 1, 0,       0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0, 0, 1,       1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0, 0, 0,       1.0f, 1.0f,
};
   cubemesh = mesh_init(cubeVertices, 36, NULL, 0);
  glEnable(GL_DEPTH_TEST);

  return true;
}

void eng_run(void) {

    mat4 transform;
  glm_mat4_identity(transform);
  
  glm_scale(transform, (vec3){0.5f, 0.5f, 0.5f});

int catotex = texture_load("/home/haraku/harakdev/physics-engine-clang/catonew.jpg");
  while (!glfwWindowShouldClose(mwindow)) {
    processInput(mwindow);

    glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    use_shader(&retshader);
    
    float s = glm_rad(90.0f);
    float angle = 0.0f;
    angle += s * getDeltaTime();
    glm_rotate_z(transform, angle, transform);
    glm_rotate_x(transform, angle, transform);
    glm_rotate_y(transform, angle, transform);
    GLuint loc = glGetUniformLocation(retshader.id, "transform");
    glUniformMatrix4fv(loc, 1, GL_FALSE, (float*)transform);

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
