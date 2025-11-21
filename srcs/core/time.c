#include <GLFW/glfw3.h>
static float fpc=0.0f;
static float prev=0.0f;
float prevF;
  int max = 0;
float getTime(){
float curr = glfwGetTime();
  fpc++;
  if(curr - prev >= 1.0){
    max = fpc;
    fpc = 0;
    prev = curr;
  }
  return max;
}
float updateTime(){
  float currF = glfwGetTime();
  float delta = currF - prevF;
  prevF = currF;
  return delta;
}
