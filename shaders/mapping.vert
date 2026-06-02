#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

out vec3 worldPosition;
out vec3 normal;
out vec3 ReflectDir;

uniform mat4 model;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

uniform bool DrawSkyBox;

void main()
{
    // World-space position for lighting calculations
    worldPosition = vec3(model * vec4(VertexPosition, 1.0));

    // Transform normal into world/view space
    normal = normalize(NormalMatrix * VertexNormal);

    if (DrawSkyBox) {
        // For the skybox: use the vertex position directly as the
        // cubemap lookup direction (cube is centered at origin)
        ReflectDir = VertexPosition;
        gl_Position = MVP * vec4(VertexPosition, 1.0);
        gl_Position = gl_Position.xyww;
    } else {
        // For regular objects: compute reflection direction
        vec3 viewDir = normalize(-worldPosition);

        ReflectDir   = reflect(-viewDir, normal);
        gl_Position = MVP * vec4(VertexPosition, 1.0);
    }
}