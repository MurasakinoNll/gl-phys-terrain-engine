#include <glad/glad.h>
#include "core/time.h"
#include "core/window.h"
#include "graphics/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/textures.h"
#include "scene/transform.h"
#include <cglm/affine.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>

#include <ft2build.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include FT_FREETYPE_H

typedef struct {
  unsigned int texture_id;  // ID handle of the glyph texture
  int size_x, size_y;       // size of glyph (width, height)
  int bearing_x, bearing_y; // offset from baseline to left/top of glyph
  unsigned int advance;     // offset to advance to next glyph
} Character;

Character char_cache[128];
static Mesh cubemesh;
static GLFWwindow *mwindow;
struct Shader retshader;
static struct Shader textshader;
static unsigned int textVAO, textVBO;

vec3 cubePositions[] = {
    // cubes will be replaced with asset loaders,
    {-2.1f, 4.6f, 1.5f},  {0.4f, -1.7f, 3.3f},  {-3.8f, 2.9f, -4.1f},
    {2.6f, -0.3f, 4.8f},  {-1.4f, 3.5f, -2.7f}, {4.2f, -4.9f, 0.6f},
    {-0.7f, 1.1f, -3.6f}, {3.1f, -2.8f, 2.4f},  {-4.3f, 0.5f, 4.7f},
    {1.8f, 4.1f, -1.2f},  {-2.9f, -3.7f, 0.3f}, {0.6f, 2.6f, -4.4f},
    {4.4f, -1.5f, 3.8f},  {-1.1f, 4.3f, -0.8f}, {2.3f, -4.2f, 1.7f},
    {-3.6f, 0.9f, 2.5f},  {1.5f, -2.6f, -3.9f}, {-4.8f, 3.2f, 0.1f},
    {0.2f, -4.7f, 4.5f},  {3.4f, 1.6f, -2.3f},  {-2.5f, -0.4f, 3.6f},
    {4.9f, 3.8f, -4.6f},  {-0.8f, -2.1f, 1.9f}, {2.7f, 4.4f, -0.5f},
    {-4.1f, -1.9f, 4.2f}, {1.3f, 0.7f, -3.1f},  {-3.2f, 4.8f, 2.8f},
    {0.9f, -3.3f, -1.6f}, {4.6f, 2.4f, 3.4f},   {-1.7f, -4.6f, 0.7f},
    {3.5f, 1.2f, -4.3f},  {-2.4f, 3.1f, 2.6f},  {0.1f, -0.6f, -2.9f},
    {-4.7f, -2.3f, 4.1f}, {2.9f, 4.7f, -1.4f},  {-0.3f, 1.4f, 3.7f},
    {4.3f, -3.9f, -0.2f}, {-1.6f, 0.2f, 4.9f},  {3.8f, -1.8f, -3.5f},
    {-3.9f, 4.5f, 1.1f},  {1.7f, -2.5f, 2.3f},  {-0.5f, 3.6f, -4.8f},
    {2.1f, -4.4f, 0.4f},  {-4.2f, 1.3f, -2.6f}, {0.8f, 2.8f, 3.2f},
    {4.7f, -0.1f, -1.8f}, {-2.8f, -3.2f, 4.6f}, {1.4f, 4.9f, -3.7f},
    {-3.3f, 2.7f, 0.2f},  {3.2f, -1.2f, 2.9f},  {-1.9f, -4.8f, -0.4f},
    {0.5f, 3.9f, 4.3f},   {-4.6f, 0.3f, -1.1f}, {2.4f, -3.1f, 3.1f},
    {-0.2f, 4.2f, -4.7f}, {4.5f, -2.7f, 1.6f},  {-3.7f, 1.8f, -2.4f}};
    float cubeVertices[] = {
      //   X           Y           Z        R      G       B              S T
      -0.5f, -0.5f, 0.5f,  1,     0,     0,     0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0,     1,     0,     1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0,
      0,     1,     1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0,     0,     1,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  1,     1,     0,     0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  1,     0,     0,     0.0f,  0.0f,  -0.5f, -0.5f,
      -0.5f, 1,     0,     1,     1.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0,
      1,     1,     0.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1,     1,     1,
      0.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1,     1,     1,     0.0f,  1.0f,
      -0.5f, 0.5f,  -0.5f, 0,     0,     0,     1.0f,  1.0f,  -0.5f, -0.5f,
      -0.5f, 1,     0,     1,     1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1,
      1,     1,     1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 1,     0,     1,
      0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0,     1,     1,     0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0,     1,     1,     0.0f,  0.0f,  -0.5f, -0.5f,
      0.5f,  1,     0,     0,     1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  1,
      1,     1,     1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0,     1,     0,
      0.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 1,     1,     0,     1.0f,  1.0f,
      0.5f,  -0.5f, -0.5f, 1,     0,     1,     1.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 1,     0,     1,     1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0,
      0,     1,     0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0,     1,     0,
      0.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 1,     1,     1,     0.0f,  1.0f,
      0.5f,  0.5f,  -0.5f, 1,     1,     0,     1.0f,  1.0f,  0.5f,  0.5f,
      0.5f,  1,     0,     0,     1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1,
      0,     0,     1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0,     1,     0,
      0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 1,     1,     1,     0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0,     0,     0,     1.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 1,     0,     0,     0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0,
      1,     0,     0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0,     1,     0,
      0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0,     0,     1,     1.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0,     0,     0,     1.0f,  1.0f,
    };
void processInput(GLFWwindow *window);

bool eng_init(void) {

  if ((mwindow = window_init()) == NULL) {
    perror("window init returns null");
    return NULL;
  }

  FT_Library ft;
  const char *font_path =
      "/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf";
  if (FT_Init_FreeType(&ft)) {
    fprintf(stderr, "ERROR::FREETYPE: Could not init FreeType Library\n");
    return false;
  }

  FT_Face face;
  if (FT_New_Face(ft, font_path, 0, &face)) {
    fprintf(stderr, "ERROR::FREETYPE: Failed to load font\n");
    return false;
  }
  FT_Set_Pixel_Sizes(face, 0, 32);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  for (unsigned char c = 0; c < 128; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      perror("failed to load glyph");
      continue;
    }
    
    int texture;
    glGenTextures(1, (GLuint *)&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RED, // Store as a single-channel texture
                 face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,
                 GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character character = {texture,
                           face->glyph->bitmap.width,
                           face->glyph->bitmap.rows,
                           face->glyph->bitmap_left,
                           face->glyph->bitmap_top,
                           (unsigned int)face->glyph->advance.x};
    char_cache[c] = character;
  }
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  FT_Done_Face(face);
  FT_Done_FreeType(ft);


  retshader = shader_init(
      "/home/haraku/harakdev/physics-engine-clang/shaders/vsh.glsl",
      "/home/haraku/harakdev/physics-engine-clang/shaders/fsh.glsl");
  cubemesh = mesh_init(cubeVertices, 36, NULL, 0);
  glEnable(GL_DEPTH_TEST);

  textshader = shader_init(
      "/home/haraku/harakdev/physics-engine-clang/shaders/text_vsh.glsl",
      "/home/haraku/harakdev/physics-engine-clang/shaders/text_fsh.glsl");

  glGenVertexArrays(1, &textVAO);
  glGenBuffers(1, &textVBO);
  glBindVertexArray(textVAO);
  glBindBuffer(GL_ARRAY_BUFFER, textVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // orthographic projection matches the same hardcoded 960x540 used in
  // transform.c's glm_perspective call
  mat4 textProjection;
  glm_ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f, textProjection);
  use_shader(&textshader);
  glUniformMatrix4fv(glGetUniformLocation(textshader.id, "projection"), 1,
                     GL_FALSE, (float *)textProjection);

  return true;
}
void render_text(unsigned int shader_program, unsigned int VAO,
                 unsigned int VBO, const char *text, float x, float y,
                 float scale, float color[3]) {

  glUseProgram(shader_program);
  glUniform3f(glGetUniformLocation(shader_program, "textColor"), color[0],
              color[1], color[2]);

  glUniform1i(glGetUniformLocation(shader_program, "text"), 0);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  for (const char *p = text; *p != '\0'; p++) {
    Character ch = char_cache[(unsigned char)*p];

    float xpos = x + ch.bearing_x * scale;
    float ypos = y - (ch.size_y - ch.bearing_y) * scale;

    float w = ch.size_x * scale;
    float h = ch.size_y * scale;

    float vertices[6][4] = {
        {xpos, ypos + h, 0.0f, 0.0f},    {xpos, ypos, 0.0f, 1.0f},
        {xpos + w, ypos, 1.0f, 1.0f},

        {xpos, ypos + h, 0.0f, 0.0f},    {xpos + w, ypos, 1.0f, 1.0f},
        {xpos + w, ypos + h, 1.0f, 0.0f}};
    glBindTexture(GL_TEXTURE_2D, ch.texture_id);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
unsigned int cato_texid = 0;
void eng_run(void) {
  cato_texid = texture_load("/home/haraku/harakdev/physics-engine-clang/catonew.jpg");
  transform_init();
  camera_init();

  // VSYNC ON||OFF
  glfwSwapInterval(0);

  while (!glfwWindowShouldClose(mwindow)) {
    processInput(mwindow);
    glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    use_shader(&retshader);
    camera_update();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cato_texid);

    glUniform1i(glGetUniformLocation(retshader.id, "objTex"), 0);
    
    transform(&retshader); 
    floor_draw(&retshader, &cubemesh, 100, 100, -3.0f, 1.0f);
    
    transform(&retshader); 
    mesh_draw(&cubemesh);

    // =========================================================================
    // STEP 2: RENDER 2D OVERLAY (Text)
    // =========================================================================
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    float color3D[3] = {1.0f, 1.0f, 1.0f};

    double dt = getFPS();
    char fps[512];
    snprintf(fps, sizeof(fps), "fps: %.0f", dt);
    render_text(textshader.id, textVAO, textVBO, fps, 25.0f, 25.0f, 1.0f, color3D);

    // =========================================================================
    // STEP 3: RESET STATE
    // =========================================================================
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glfwSwapBuffers(mwindow);
    glfwPollEvents();
  }
}

void eng_term(void) {
  remove_shader(&retshader);
  mesh_remove(&cubemesh);
  glfwTerminate();
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
  vec3 tempcam;
  const float cameraSpeed = 2.5f * updateTime();
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.cameraFront, cameraSpeed, tempcam);
    glm_vec3_add(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.cameraFront, cameraSpeed, tempcam);
    glm_vec3_sub(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    glm_vec3_cross(Ecamera.cameraFront, Ecamera.up, tempcam);
    glm_vec3_normalize(tempcam);
    glm_vec3_scale(tempcam, cameraSpeed, tempcam);
    glm_vec3_add(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    glm_vec3_cross(Ecamera.cameraFront, Ecamera.up, tempcam);
    glm_vec3_normalize(tempcam);
    glm_vec3_scale(tempcam, cameraSpeed, tempcam);
    glm_vec3_sub(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.up, cameraSpeed, tempcam);
    glm_vec3_add(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    glm_vec3_scale(Ecamera.up, cameraSpeed, tempcam);
    glm_vec3_sub(Ecamera.cameraPos, tempcam, Ecamera.cameraPos);
  }
}
