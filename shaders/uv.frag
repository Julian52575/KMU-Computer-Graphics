#version 400

out vec4 FragColor;

uniform sampler2D tex;
in vec2 TexCoord;

uniform bool hasTexture;

// Phong
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

vec4 getPhongColor()
{
	vec3 N = normalize(normal);
	vec3 L = normalize(vec3(LightPosition) - positionInCamera);
	vec3 V = normalize(-positionInCamera);
	vec3 R = reflect(-L, N);
	vec3 diffuse = objectMaterial.Kd * LightIntensity * max(dot(N, L), 0.0);
	vec3 ambient = objectMaterial.Ka * LightIntensity;
	vec3 specular = objectMaterial.Ks * LightIntensity * pow(max(dot(R, V), 0.0), objectMaterial.shininess);
	vec3 color = ambient + diffuse + specular;
	
	return vec4(color, 1.0);
}

void main()
{
	vec4 texColor;
	
	if (hasTexture) {
		texColor = texture( tex, TexCoord );
		FragColor = getPhongColor() + texColor;
	} else {
		FragColor = getPhongColor();
	}
}