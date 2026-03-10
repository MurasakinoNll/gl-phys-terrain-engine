#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "graphics/shader.h"
#include <cglm/types.h>
typedef struct{
  mat4 model, view, projection;
  vec3 normalized_x, normalized_y, normalized_z;
} Views;
void floor_draw(struct Shader *shader, int length, int width, float y, float spacing);
void transform_init();
void transform(const struct Shader *shader);
#endif // !TRANSFORM_H
