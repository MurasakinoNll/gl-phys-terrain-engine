#include "core/engine.h"
int main() { 
  if(!eng_init())return 1;
  eng_run();
  eng_term();
  return 0;
}
