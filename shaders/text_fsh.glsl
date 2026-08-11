// exp: new file, needed because fsh.glsl has no textColor uniform and
// expects an RGB texture + vertex color, not a single-channel glyph bitmap
#version 460 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
