#version 430 core

in vec3 worldPosition;
in vec3 normal;
uniform vec4 LightPosition;
uniform vec3 LightIntensity = vec3(1.0, 1.0, 1.0);

struct Material  {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float shininess;
	vec3 refractRGB;
};
uniform Material objectMaterial;
float DoNotOptimizeMaterial()
{
	return objectMaterial.Ka.x + objectMaterial.Kd.y + objectMaterial.Ks.z
		+ objectMaterial.shininess + objectMaterial.refractRGB.x;
}

out vec4 FragColor;

uniform vec3 WorldCameraPosition;

uniform mat4 MVP;
uniform samplerCube CubeMapTex;

in vec3 reflectDir;
in vec3 refractDir;
float reflectFactor = 0.2f;

vec3 getPhongColor()
{
	vec3 N = normalize(normal);
	vec3 L = normalize(vec3(LightPosition) - worldPosition);
	vec3 V = normalize(-worldPosition);
	vec3 R = reflect(-L, N);
	vec3 diffuse = objectMaterial.Kd * LightIntensity * max(dot(N, L), 0.0);
	vec3 ambient = objectMaterial.Ka * LightIntensity;
	vec3 specular = objectMaterial.Ks * LightIntensity * pow(max(dot(R, V), 0.0), objectMaterial.shininess);
	
	return ambient + diffuse + specular;
}

void main()
{
	FragColor = vec4(DoNotOptimizeMaterial());
    vec3 N = normalize(normal);
    vec3 V = normalize(-WorldCameraPosition);
	vec3 I = normalize(worldPosition - WorldCameraPosition);
	vec3 reflectDir = reflect(I, N);
		vec3 refractDirR = refract(I, N, 1.0003f / objectMaterial.refractRGB.r);
		vec3 refractDirG = refract(I, N, 1.0003f / objectMaterial.refractRGB.g);
		vec3 refractDirB = refract(I, N, 1.0003f / objectMaterial.refractRGB.b);

    vec4 reflectColor = texture(CubeMapTex, normalize(reflectDir));
    vec4 refractColor;
		refractColor.r = texture(CubeMapTex, normalize(refractDirR)).r;
		refractColor.g = texture(CubeMapTex, normalize(refractDirG)).g;
		refractColor.b = texture(CubeMapTex, normalize(refractDirB)).b;
	//float fresnel = pow(1.0 - max(dot(-I, N), 0.0), 5.0);

	refractColor.rgb *= getPhongColor();
    FragColor = mix(refractColor, reflectColor,
		//fresnel
		reflectFactor
	);
}