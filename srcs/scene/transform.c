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
  getTime();
  glm_mat4_identity(coordsystem.model);              // 2x 4x4 identity matricies
  glm_mat4_identity(coordsystem.view);

  glm_vec3_copy((vec3){1.0f, 0.0f, 0.0f}, coordsystem.normalized_x);    // normalized x coords for when doing scale
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, coordsystem.normalized_y);    // such that a single matrix can contain scale & transform
  glm_vec3_copy((vec3){0.0f, 0.0f, 1.0f}, coordsystem.normalized_z);    // where  S1 S2 S3 are the posiitions of normalized x y z 
                                                                                             // while column 4 is a vec4 of transforms on X Y Z W
  glm_quat_identity(cube.quat);  // identity quat is just 1 + 0i + 0j + 0k
                                    // versors are quaternions of length/mag 1

  glm_vec3_copy((vec3){0.0f, 0.0f,  0.0f}, cube.pos);
}
void transform(const struct Shader *shader) {
  glm_quat_mat4(cube.quat, coordsystem.model); // ijk vec -> float[4][4]
  glm_translate(coordsystem.model, cube.pos); //translate model to align with pos, therefore moving model by pos
  
  //rotation logic
  float dt = updateTime();
  float speed = 90.0f;
  float angle = glm_rad(speed*dt);
  versor r;

  glm_quatv(r, angle, (vec3){3.0f, 1.0f, 1.0f}); //creating some rotation vector on some axis, where vec3 of axis represents rotation axis
  glm_quat_mul(cube.quat, r, cube.quat); // apply rotation quat to cube quat
 glm_quat_normalize(cube.quat);

  glm_mat4_identity(coordsystem.model); // model space identity mat4
  // glm_translate(coordsystem.model, cube.pos);   ???????
  mat4 rot;
  glm_quat_mat4(cube.quat, rot); 
  glm_mat4_mul(coordsystem.model, rot, coordsystem.model);

  //                     fov                      aspect ratio                      maxZ to render          projection matrix
  glm_perspective(glm_rad(45.0f), 960.0f/540.0f, 0.1f, 100000.0f, coordsystem.projection);
  glm_mat4_copy(Ecamera.view, coordsystem.view);
  
  int modelLoc = glGetUniformLocation(shader->id, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)coordsystem.model);

  int viewLoc = glGetUniformLocation(shader->id, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float *)coordsystem.view);

  int projectionLoc = glGetUniformLocation(shader->id, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float *)coordsystem.projection);

}
void floor_draw(struct Shader *shader, int length, int width, float y, float spacing) {
  int modelLoc = glGetUniformLocation(shader->id, "model");

  for(int x = 0; x < length; x++) {
    for(int z = 0; z < width; z++) {
        mat4 model;
        glm_mat4_identity(model);
        vec3 pos = {(x - length/2.0f) * spacing,y,(z - width/2.0f)  * spacing};
        glm_translate(model, pos);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  }
}
