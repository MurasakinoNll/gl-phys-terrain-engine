#version 460 core 
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCord;

uniform sampler2D objTex;
void main()
{
FragColor = texture(objTex, texCord);
}
