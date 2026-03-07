#include <stddef.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
typedef struct {
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
  size_t index_count;
  size_t vertex_count;
} Mesh;

Mesh mesh_init(const float *vertices, size_t vertex_count, const unsigned int *indices, size_t index_count){
  Mesh mesh;
  mesh.ebo = 0;
  mesh.index_count = index_count;
  mesh.vertex_count = vertex_count;
  glGenVertexArrays(1,&mesh.vao);
  glGenBuffers(1, &mesh.vbo);
  if(indices)glGenBuffers(1, &mesh.ebo);

  glBindVertexArray(mesh.vao);

  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
  glBufferData(GL_ARRAY_BUFFER, vertex_count*8*sizeof(float), vertices, GL_STATIC_DRAW);
  if(indices && index_count > 0){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count*sizeof(unsigned int), indices, GL_STATIC_DRAW);
  }
  //vertex attrib
  glVertexAttribPointer(0, 3, GL_FLOAT,
  GL_FALSE, 8*sizeof(float), (void*)0);
  
  //color attrib
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
  8*sizeof(float),(void*)(3*sizeof(float)));
  
  //tex attrub
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6*sizeof(float)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);
  return mesh;
}

void mesh_draw(const Mesh *mesh){
  glBindVertexArray(mesh->vao);
  if(mesh->ebo)glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
  else glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
}

void mesh_remove(const Mesh *mesh){
  glDeleteBuffers(1, &mesh->vbo);
}
