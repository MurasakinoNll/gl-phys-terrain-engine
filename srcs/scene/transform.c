#include <cglm/quat.h>
#include <glad/glad.h>
#include "core/time.h"
#include "graphics/camera.h"
#include "graphics/shader.h"
#include <cglm/cam.h>
#include <cglm/cglm.h>
#include <cglm/io.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <cglm/vec3.h>
  float rotS = 0.001f;
  float rotA = 0.0f;

#include <cglm/vec3-ext.h>
typedef struct{
  mat4 model, view, projection;
  vec3 normalized_x, normalized_y, normalized_z;
} Views;
typedef struct{
  vec3 pos;
  versor quat;
} ComplexDiscriptor;
Views coordsystem;
ComplexDiscriptor cube;
void transform_init() {
  glm_mat4_identity(coordsystem.model);
  glm_mat4_identity(coordsystem.view);
  glm_vec3_copy((vec3){1.0f, 0.0f, 0.0f}, coordsystem.normalized_x);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, coordsystem.normalized_y);
  glm_vec3_copy((vec3){0.0f, 0.0f, 1.0f}, coordsystem.normalized_z);

  glm_quat_identity(cube.quat);
  glm_vec3_copy((vec3){0.0f, 3.0f,  0.0f}, cube.pos);

}
void transform(const struct Shader *shader) {
  //versor rotation;
  // float dt = updateTime();
  // float dx = 5.0f;
  // float theta = glm_rad(dx * dt);
  //
  // glm_quatv(rotation, theta, coordsystem.normalized_y);
  // glm_quat_mul(cube.quat, rotation, cube.quat);
  // glm_quat_normalize(cube.quat);
  //

     glm_quat_mat4(cube.quat, coordsystem.model);

    glm_translate(coordsystem.model, cube.pos);

   float dt = updateTime();
    float speed = 0.0f;
    float angle = glm_rad(speed*dt);

    versor r;
    glm_quatv(r, angle, (vec3){1.0f, 1.0f, 1.0f});
    glm_quat_mul(cube.quat, r, cube.quat);
    glm_quat_normalize(cube.quat);

    glm_mat4_identity(coordsystem.model);

    glm_translate(coordsystem.model, cube.pos);

    mat4 rot;
    glm_quat_mat4(cube.quat, rot);

    glm_mat4_mul(coordsystem.model, rot, coordsystem.model);


    glm_perspective(glm_rad(45.0f), 960.0f/540.0f, 0.1f, 100.0f, coordsystem.projection);
  fprintf(stdout, "cube pos: %.2f %.2f %.2f\n", cube.pos[0], cube.pos[1], cube.pos[2]);
fprintf(stdout, "cam pos:  %.2f %.2f %.2f\n", Ecamera.cameraPos[0], Ecamera.cameraPos[1], Ecamera.cameraPos[2]);
fprintf(stdout, "cam front:%.2f %.2f %.2f\n", Ecamera.cameraFront[0], Ecamera.cameraFront[1], Ecamera.cameraFront[2]);
  fprintf(stdout, "view[3]: %.2f %.2f %.2f\n", 
    Ecamera.view[3][0], 
    Ecamera.view[3][1], 
    Ecamera.view[3][2]);
    
  glm_mat4_copy(Ecamera.view, coordsystem.view);
  int modelLoc = glGetUniformLocation(shader->id, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)coordsystem.model);

  int viewLoc = glGetUniformLocation(shader->id, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float *)coordsystem.view);

  int projectionLoc = glGetUniformLocation(shader->id, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float *)coordsystem.projection);

}
