#include <glad/glad.h>

#include "core/time.h"
#include "core/window.h"
#include "graphics/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/textures.h"
#include "scene/transform.h"
#include <cglm/affine.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <freetype2/ft2build.h>
#include <stdbool.h>
#include <unistd.h>
#include FT_FREETYPE_H

static Mesh cubemesh;
static GLFWwindow *mwindow;
struct Shader retshader;

vec3 cubePositions[] = {
    {1.2f, -3.4f, 2.1f},  {-4.5f, 0.8f, -1.3f}, {3.7f, 2.2f, -0.9f},
    {-2.1f, 4.6f, 1.5f},  {0.4f, -1.7f, 3.3f},  {-3.8f, 2.9f, -4.1f},
    {2.6f, -0.3f, 4.8f},  {-1.4f, 3.5f, -2.7f}, {4.2f, -4.9f, 0.6f},
    {-0.7f, 1.1f, -3.6f}, {3.1f, -2.8f, 2.4f},  {-4.3f, 0.5f, 4.7f},
    {1.8f, 4.1f, -1.2f},  {-2.9f, -3.7f, 0.3f}, {0.6f, 2.6f, -4.4f},
    {4.4f, -1.5f, 3.8f},  {-1.1f, 4.3f, -0.8f}, {2.3f, -4.2f, 1.7f},
    {-3.6f, 0.9f, 2.5f},  {1.5f, -2.6f, -3.9f}, {-4.8f, 3.2f, 0.1f},
    {0.2f, -4.7f, 4.5f},  {3.4f, 1.6f, -2.3f},  {-2.5f, -0.4f, 3.6f},
    {4.9f, 3.8f, -4.6f},  {-0.8f, -2.1f, 1.9f}, {2.7f, 4.4f, -0.5f},
    {-4.1f, -1.9f, 4.2f}, {1.3f, 0.7f, -3.1f},  {-3.2f, 4.8f, 2.8f},
    {0.9f, -3.3f, -1.6f}, {4.6f, 2.4f, 3.4f},   {-1.7f, -4.6f, 0.7f},
    {3.5f, 1.2f, -4.3f},  {-2.4f, 3.1f, 2.6f},  {0.1f, -0.6f, -2.9f},
    {-4.7f, -2.3f, 4.1f}, {2.9f, 4.7f, -1.4f},  {-0.3f, 1.4f, 3.7f},
    {4.3f, -3.9f, -0.2f}, {-1.6f, 0.2f, 4.9f},  {3.8f, -1.8f, -3.5f},
    {-3.9f, 4.5f, 1.1f},  {1.7f, -2.5f, 2.3f},  {-0.5f, 3.6f, -4.8f},
    {2.1f, -4.4f, 0.4f},  {-4.2f, 1.3f, -2.6f}, {0.8f, 2.8f, 3.2f},
    {4.7f, -0.1f, -1.8f}, {-2.8f, -3.2f, 4.6f}, {1.4f, 4.9f, -3.7f},
    {-3.3f, 2.7f, 0.2f},  {3.2f, -1.2f, 2.9f},  {-1.9f, -4.8f, -0.4f},
    {0.5f, 3.9f, 4.3f},   {-4.6f, 0.3f, -1.1f}, {2.4f, -3.1f, 3.1f},
    {-0.2f, 4.2f, -4.7f}, {4.5f, -2.7f, 1.6f},  {-3.7f, 1.8f, -2.4f}};
void processInput(GLFWwindow *window);

bool eng_init(void) {

  mwindow = window_init();

  retshader = shader_init(
      "/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl",
      "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
  float cubeVertices[] = {
      //   X           Y           Z        R      G       B              S T
      -0.5f, -0.5f, 0.5f,  1,     0,     0,     0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0,     1,     0,     1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0,
      0,     1,     1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0,     0,     1,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  1,     1,     0,     0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  1,     0,     0,     0.0f,  0.0f,  -0.5f, -0.5f,
      -0.5f, 1,     0,     1,     1.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0,
      1,     1,     0.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1,     1,     1,
      0.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1,     1,     1,     0.0f,  1.0f,
      -0.5f, 0.5f,  -0.5f, 0,     0,     0,     1.0f,  1.0f,  -0.5f, -0.5f,
      -0.5f, 1,     0,     1,     1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1,
      1,     1,     1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 1,     0,     1,
      0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0,     1,     1,     0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0,     1,     1,     0.0f,  0.0f,  -0.5f, -0.5f,
      0.5f,  1,     0,     0,     1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1,
      1,     1,     1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0,     1,     0,
      0.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1,     1,     0,     1.0f,  1.0f,
      0.5f,  -0.5f, -0.5f, 1,     0,     1,     1.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 1,     0,     1,     1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0,
      0,     1,     0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0,     1,     0,
      0.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 1,     1,     1,     0.0f,  1.0f,
      0.5f,  0.5f,  -0.5f, 1,     1,     0,     1.0f,  1.0f,  0.5f,  0.5f,
      0.5f,  1,     0,     0,     1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1,
      0,     0,     1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0,     1,     0,
      0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 1,     1,     1,     0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0,     0,     0,     1.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 1,     0,     0,     0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0,
      1,     0,     0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0,     1,     0,
      0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0,     0,     1,     1.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0,     0,     0,     1.0f,  1.0f,
  };
  cubemesh = mesh_init(cubeVertices, 36, NULL, 0);
  glEnable(GL_DEPTH_TEST);

  return true;
}

void eng_run(void) {
  //
  texture_load("/home/haraku/harakdev/physics-engine-clang/catonew.jpg");
  transform_init();
  camera_init();

  // VSYNC ON||OFF
  glfwSwapInterval(0);
  while (!glfwWindowShouldClose(mwindow)) {
    processInput(mwindow);
    glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    use_shader(&retshader);
    // int modelLoc = glGetUniformLocation(retshader.id, "model");
    // for (unsigned int i = 0; i < 20; i++) {
    //   mat4 model;
    //   glm_mat4_identity(model);
    //   glm_translate(model, cubePositions[i]);
    //   float angle = 10.0f * i;
    //   glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
    //   glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)model);
    //   glDrawArrays(GL_TRIANGLES, 0, 36);
    // }
    floor_draw(&retshader, 100, 100, -3.0f, 1.0f);
    camera_update();
    transform(&retshader);

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
  vec3 tempcam;
  const float cameraSpeed = 2.5f * updateTime();
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.cameraFront, cameraSpeed, tempcam);
    glm_vec3_add(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
    // fprintf(stdout, "pos(%.2f, %.2f, %.2f) front(%.2f, %.2f, %.2f)\n",
    //  Ecamera.cameraPos[0], Ecamera.cameraPos[1], Ecamera.cameraPos[2],
    //  tempcam[0], tempcam[1], tempcam[2]);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.cameraFront, cameraSpeed, tempcam);
    glm_vec3_sub(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
    // fprintf(stdout, "pos(%.2f, %.2f, %.2f) front(%.2f, %.2f, %.2f)\n",
    //   Ecamera.cameraPos[0], Ecamera.cameraPos[1], Ecamera.cameraPos[2],
    //   tempcam[0], tempcam[1], tempcam[2]);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    glm_vec3_cross(Ecamera.cameraFront, Ecamera.up, tempcam);
    glm_vec3_normalize(tempcam);
    glm_vec3_scale(tempcam, cameraSpeed, tempcam);
    glm_vec3_add(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
    // fprintf(stdout, "pos(%.2f, %.2f, %.2f) front(%.2f, %.2f, %.2f)\n",
    //   Ecamera.cameraPos[0], Ecamera.cameraPos[1], Ecamera.cameraPos[2],
    //   tempcam[0], tempcam[1], tempcam[2]);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    glm_vec3_cross(Ecamera.cameraFront, Ecamera.up, tempcam);
    glm_vec3_normalize(tempcam);
    glm_vec3_scale(tempcam, cameraSpeed, tempcam);
    glm_vec3_sub(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
    // fprintf(stdout, "pos(%.2f, %.2f, %.2f) front(%.2f, %.2f, %.2f)\n",
    //     Ecamera.cameraPos[0], Ecamera.cameraPos[1], Ecamera.cameraPos[2],
    //     tempcam[0], tempcam[1], tempcam[2]);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.up, cameraSpeed, tempcam);
    glm_vec3_add(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.up, cameraSpeed, tempcam);
    glm_vec3_sub(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
}
