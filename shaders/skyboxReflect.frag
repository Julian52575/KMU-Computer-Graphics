#version 430 core

in vec3 worldPosition;
in vec3 normal;
uniform vec4 LightPosition;
uniform vec3 LightIntensity;

struct Material {
    vec3 Kd;
    vec3 Ka;
    vec3 Ks;
    float shininess;
    float eta;
};
uniform Material objectMaterial;
uniform float reflectFactor = 0.3;

out vec4 FragColor;

in vec3 ReflectDir;
uniform bool DrawSkyBox = false;
uniform mat4 MVP;
uniform samplerCube CubeMapTex;

void main()
{
    // No optimizing uniform away
    FragColor = vec4(objectMaterial.eta);
    //
    vec4 CubeMapColor = texture(CubeMapTex, ReflectDir);

    if (DrawSkyBox) {
        // Render the skybox faces directly using the cubemap color
        FragColor = CubeMapColor;
    } else {
        // Phong lighting + reflection for regular objects
        vec3 n = normalize(normal);
        vec3 lightDir = normalize(vec3(LightPosition) - worldPosition);
        vec3 viewDir  = normalize(-worldPosition);  // assumes view-space position
        vec3 reflDir  = reflect(-lightDir, n);

        vec3 ambient  = LightIntensity * objectMaterial.Ka;
        vec3 diffuse  = LightIntensity * objectMaterial.Kd * max(dot(lightDir, n), 0.0);
        vec3 specular = LightIntensity * objectMaterial.Ks
                        * pow(max(dot(reflDir, viewDir), 0.0), objectMaterial.shininess);

        vec3 phong = ambient + diffuse + specular;

        // Blend Phong lighting with cubemap reflection
        FragColor = vec4(phong, 1.0) + 0.3 * CubeMapColor;
    }
}