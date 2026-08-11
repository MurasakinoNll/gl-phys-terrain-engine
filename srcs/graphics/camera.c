#include "graphics/camera.h"
#include <cglm/cam.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <cglm/vec3.h>
#include <math.h>
struct Camera Ecamera;
struct Direction Edirection;
void camera_init(){
      Edirection.pitch = 0.0f;
    Edirection.yaw = -90.0f; 
    glm_vec3_copy((vec3){0.0f, 0.0f,  3.0f}, Ecamera.cameraPos);
    glm_vec3_copy((vec3){0.0f, 0.0f,  0.0f}, Ecamera.cameraTarget);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, Ecamera.cameraFront);
    glm_vec3_copy((vec3){0.0f, 1.0f,  0.0f}, Ecamera.up);
    vec3 fpos;
    glm_vec3_add(Ecamera.cameraPos, Ecamera.cameraFront, fpos);
    glm_lookat(Ecamera.cameraPos, fpos, Ecamera.up, Ecamera.view);
}
void camera_update(){
  vec3 target;
  Ecamera.cameraFront[0] = cos(glm_rad(Edirection.yaw)) * cos(glm_rad(Edirection.pitch));
    Ecamera.cameraFront[1] = sin(glm_rad(Edirection.pitch));
    Ecamera.cameraFront[2] = sin(glm_rad(Edirection.yaw)) * cos(glm_rad(Edirection.pitch));
    glm_vec3_normalize(Ecamera.cameraFront);
  glm_vec3_add(Ecamera.cameraPos,Ecamera.cameraFront, target);
  glm_lookat(Ecamera.cameraPos, target, Ecamera.up, Ecamera.view);
  }
