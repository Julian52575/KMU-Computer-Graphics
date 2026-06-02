#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

out vec3 worldPosition;
out vec3 normal;
out vec3 ReflectDir;

uniform mat4 model; // Model matrix
uniform mat3 NormalMatrix;
uniform mat4 MVP;

uniform bool DrawSkyBox;

uniform vec3 WorldCameraPosition;

void main()
{
    // World-space position for lighting calculations
    worldPosition = vec3(model * vec4(VertexPosition, 1.0));

    // Transform normal into world/view space
    normal = normalize(NormalMatrix * VertexNormal);

    gl_Position = MVP * vec4(VertexPosition, 1.0);
    if (DrawSkyBox) {
        // For the skybox: use the vertex position directly as the
        // cubemap lookup direction (cube is centered at origin)
        ReflectDir = VertexPosition;
        gl_Position = gl_Position.xyww;
    } else {
        // N: Normal in world space
        vec3 N = normalize(normal);

        // P: Vertex position in world space
        vec3 P = worldPosition;

        // V: Direction from surface point to camera in world space
        vec3 V = normalize(WorldCameraPosition - P);

        // ReflectDir: Reflect the view ray around the normal
        // reflect() expects the incident direction (toward surface), so negate V
        ReflectDir = reflect(-V, N);
    }
}