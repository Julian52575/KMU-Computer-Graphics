#version 450 

layout(location = 0) in vec4 coord3d; // 0: attrib # (pos)
layout(location = 1) in vec3 v_color;  // 1: attrib (color)

// data to fragment shader (out)
out vec3 f_color;

uniform mat4 Model;  //4x4 matrix from app.

void main()
{
 
   gl_Position =  coord3d;
   f_color = v_color;

}