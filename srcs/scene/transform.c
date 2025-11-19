#include "core/time.h"
#include "graphics/shader.h"
#include <cglm/cam.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <glad/glad.h>
  float rotS = 0.001f;
  float rotA = 0.0f;

Time proper;
void transform_init(const struct Shader *shader) {
  time_update(&proper);
  vec3 normalized_x = {1.0f, 1.0f, 0.0f};
  vec3 m3_z = {0.0f, 0.0f, -3.0f};
  mat4 model, view, projection;
  glm_mat4_identity(model);
  glm_mat4_identity(view);
  glm_rotate(model, glm_rad(15.0f), normalized_x);
  glm_translate(view, m3_z);
  glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);

  rotA += rotS * proper.delta;
  glm_rotate(projection, glm_rad(5.0f), normalized_x);
  // seperate into loop
  int modelLoc = glGetUniformLocation(shader->id, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)model);

  int viewLoc = glGetUniformLocation(shader->id, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float *)view);

  int projectionLoc = glGetUniformLocation(shader->id, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float *)projection);
}
