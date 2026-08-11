#include <GLFW/glfw3.h>
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
    return max;
}
double updateTime(){
  double currF = glfwGetTime();
  double delta = currF - prevF;
  prevF = currF;
  return delta;
}
double getFPS() {
    static double prev = 0.0;
    static int fpc = 0;
    static double currentFPS = 0.0;

    double curr = glfwGetTime();
    fpc++;

    if (curr - prev >= 0.1) {
        currentFPS = fpc / (curr - prev); 
        
        fpc = 0;
        prev = curr;
    }
    return currentFPS; 
}
