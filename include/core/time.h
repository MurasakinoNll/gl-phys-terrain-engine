#ifndef TIME_H
#define TIME_H

typedef struct Time {
  double now;
  double last;
  float delta;
  double realtime;
} Time;

void time_init(Time *t);
void time_update(Time *t);

#endif
