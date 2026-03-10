#version 450 


layout(location = 0) in vec4 pos;  //0: attrib # (pos)
layout(location = 1) in vec3 color;  //1 : attrib # (color)

//data to fragment shader
out vec3 c;


void main()
{
	c = color;

	// clip coordinate : gl_Position
	gl_Position = pos;
}
