#version 430 core

in vec3 worldPosition;
in vec3 normal;
uniform vec4 LightPosition;
uniform vec3 LightIntensity; //Ia=Id=Is

struct Material  {
	vec3 Kd;
	vec3 Ka;
	vec3 Ks;
	float shininess;
};
uniform Material objectMaterial;

out vec4 FragColor;

uniform bool isSilhouette = false;
uniform vec3 sColor =  vec3(0.0, 0.0, 0.0);
uniform vec2 resolution = vec2(800.0, 600.0);

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

const int levels = 3;
vec3 getCartonColor()
{
	if (isSilhouette)
	{
		return sColor;
	}
	vec3 N = normalize(normal);
	vec3 L = normalize(vec3(LightPosition) - worldPosition);
	const float scaleFactor = 1.0 / levels;
	float cosine = dot(L, N);  //This value has (0~1)
	float value = floor( cosine * levels ) * scaleFactor;

	vec3 diffuse = objectMaterial.Kd * LightIntensity * max(dot(N, L), 1.0);
	vec3 ambient = objectMaterial.Ka * LightIntensity;

	return (diffuse + ambient + value);
}

void main()
{
	
	//if (gl_FragCoord.x < resolution.x * 0.5)
	//{
		//cartoon
		FragColor = vec4(getCartonColor(), 1.0);
	//}
	//else
	//{
		//phong
		//FragColor = vec4(getPhongColor(), 1.0);
	//}
}