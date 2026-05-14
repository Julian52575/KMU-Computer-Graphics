#version 400

in vec3 positionInCamera;
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

void main()
{
	vec3 N = normalize(normal);
	vec3 L = normalize(vec3(LightPosition) - positionInCamera);
	vec3 V = normalize(-positionInCamera);
	vec3 R = reflect(-L, N);
	vec3 diffuse = objectMaterial.Kd * LightIntensity * max(dot(N, L), 0.0);
	vec3 ambient = objectMaterial.Ka * LightIntensity;
	vec3 specular = objectMaterial.Ks * LightIntensity * pow(max(dot(R, V), 0.0), objectMaterial.shininess);
	vec3 color = ambient + diffuse + specular;
	
	FragColor = vec4(color, 1.0);
}