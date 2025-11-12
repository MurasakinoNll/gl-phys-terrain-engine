#ifndef SHADER_H
#define SHADER_H

struct Shader{unsigned int id;};

struct Shader shader_init(const char *vshpath, const char *fshpath);
void use_shader(struct Shader *shader);
void remove_shader(struct Shader *shader);
#endif // !SHADER_H
