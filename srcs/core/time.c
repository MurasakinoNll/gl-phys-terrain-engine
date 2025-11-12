#include <GLFW/glfw3.h>
static float deltatime = 0.0f;
static float lastframe = 0.0f;
float getframes(void){
  float currentframe = glfwGetTime();
  deltatime = currentframe - lastframe;
  lastframe = currentframe;
  return deltatime;
}
