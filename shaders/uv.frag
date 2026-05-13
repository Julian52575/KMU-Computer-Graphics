#version 400

out vec4 FragColor;

uniform sampler2D tex;
in vec2 TexCoord;

void main()
{
   FragColor = texture(tex, TexCoord);
}