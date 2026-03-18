#include <GLFW/glfw3.h>
#include <stdio.h>
static double fpc=0.0f;
static double prev=0.0f;
double prevF = 0;
double max = 0;
double getTime(){
double curr = glfwGetTime();
  fpc++;
  if(curr - prev >= 0.1){
    max = fpc;
    fpc = 0;
    prev = curr;
  }
  printf("curr=%f prev=%f max=%f\n", curr, prev, max);
  return max;
}
double updateTime(){
  double currF = glfwGetTime();
  double delta = currF - prevF;
  prevF = currF;
  return delta;
}
