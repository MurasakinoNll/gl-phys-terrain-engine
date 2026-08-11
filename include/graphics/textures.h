#ifndef TEXTURES_H
#define TEXTURES_H

#include <stb/stb_image.h>
struct Texture{
  int width;
  int height;
  int channelc;
  unsigned char* data;
  unsigned int gltexture;
};

int texture_load(const char* ptexturepath);

#endif // !TEXTURES_H

