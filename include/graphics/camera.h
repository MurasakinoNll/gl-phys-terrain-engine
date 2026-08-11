#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW/glfw3.h>
#include <cglm/types.h>
struct  Camera{
  vec3 cameraPos;
  vec3 cameraTarget;
  vec3 cameraFront;
  vec3 up; 
  mat4 view;
};
struct Direction{
  float pitch, yaw;
};
extern struct Camera Ecamera;
extern struct Direction Edirection;

void camera_init();
void camera_update();

#endif
