#include <GLFW/glfw3.h>
typedef struct {
  double curr, prev, realt;
  float delta;
} Time;
void time_init(Time *t) {
  t->prev = glfwGetTime();
  t->curr = t->prev;
  t->delta = 0.0f;
  t->realt = 0.0;
}
void time_update(Time *t) {
  t->curr = glfwGetTime();
  t->delta = (float)(t->curr - t->prev);
  t->prev = t->curr;
  t->realt += t->delta;
}
