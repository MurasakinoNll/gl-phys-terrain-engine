#include "utils/io.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

struct Shader {
  unsigned int id;
};


struct Shader shader_init(const char *vshpath, const char *fshpath){
  char *vshsource = loadshader(vshpath);
  char *fshsource = loadshader(fshpath);
  unsigned int vertexShader, fragmentShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertexShader, 1, (const GLchar**)&vshsource, NULL);
  glShaderSource(fragmentShader, 1, (const GLchar**)&fshsource, NULL);
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  //logging
  char infoLog[1024];
  int vshsuc, fshsuc;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vshsuc);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fshsuc);
  if(!vshsuc || !fshsuc){
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
  perror("failed shader compile");
  }

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  //logging
  int success; glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success){glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);perror("failed shader link");}
  
  struct Shader shader;
  shader.id = shaderProgram;
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  free(vshsource);
  free (fshsource);
  return shader;
}

void use_shader(struct Shader *shader){
  glUseProgram(shader->id);
}

void remove_shader(struct Shader *shader){
  glDeleteProgram(shader->id);
}
