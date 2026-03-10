#include <GLFW/glfw3.h>
static double fpc=0.0f;
static double prev=0.0f;
double prevF;
  int max = 0;
double getTime(){
double curr = glfwGetTime();
  fpc++;
  if(curr - prev >= 1.0){
    max = fpc;
    fpc = 0;
    prev = curr;
  }
  return max;
}
double updateTime(){
  double currF = glfwGetTime();
  double delta = currF - prevF;
  prevF = currF;
  return delta;
}
