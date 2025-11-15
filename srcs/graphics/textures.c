#include <stb/stb_image.h>
struct Texture{
  int width;
  int height;
  int channelc;
  unsigned char* data;
  unsigned int gltexture;
};
#include <stdio.h>
#include <glad/glad.h>

int texture_load(const char* ptexturepath){
  stbi_set_flip_vertically_on_load(1);
  struct Texture currTex;
  currTex.data = stbi_load(ptexturepath, &currTex.width, &currTex.height, &currTex.channelc, 0);
  if(!currTex.data){perror("failed to load texture");}
  glGenTextures(1, &currTex.gltexture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, currTex.gltexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum format = (currTex.channelc == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, currTex.width, currTex.height, 0, format, GL_UNSIGNED_BYTE, currTex.data);

  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(currTex.data);
  return currTex.gltexture;
}
