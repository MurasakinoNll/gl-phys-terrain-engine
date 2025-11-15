#ifndef MESH_H
#define MESH_H

#include <stddef.h>

typedef struct {
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
  size_t index_count;
  size_t vertex_count;
} Mesh;

Mesh mesh_init(const float *vertices, size_t vertex_count,
               const unsigned int *indices, size_t index_count);
void mesh_draw(const Mesh *mesh);
void mesh_remove(const Mesh *mesh);

#endif // !MESH_H
