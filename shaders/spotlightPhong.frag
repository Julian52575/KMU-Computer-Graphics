#version 400

in vec3 PositionInCamera;
in vec4 glPosition;
in vec3 Normal;


struct Material  {
	vec3 Kd;
	vec3 Ka;
	vec3 Ks;
	float shininess;
};
uniform Material objectMaterial;

struct Spot
{ 
	vec4 position; 
	vec3 direction; 
	vec3 intensity; 
	float exponent; 
	float cutoff; 
//광원의 위치
//광원의 direction
//광원의 색상 (1,1,1)
//20.0
//radian(30)
	float innerCutoff; //radian(20)
	Material material;
}; 
uniform Spot spot; 
const float constantAttenuation = 1.0; 
const float linearAttenuation = 0.01f; 
const float quadraticAttenuation = 0.001f;

out vec4 FragColor;

float getAttenuation(float d)
{
	return 1.0 / (
		constantAttenuation +
		(linearAttenuation * d) +
		(quadraticAttenuation * d * d)
	);
}

vec4 phong(vec3 L, float attenuation)
{
	vec3 N = normalize(Normal);
	vec3 V = normalize(-PositionInCamera.xyz);
	float LDotN = max(dot(L, N), 0.0);
	vec3 H = normalize(L + V);

	vec3 ambient = spot.material.Ka * objectMaterial.Ka * spot.intensity * attenuation;
	vec3 diffuse = spot.material.Kd * objectMaterial.Kd * max(LDotN,0) * spot.intensity * attenuation;
	vec3 specular = spot.material.Ks * objectMaterial.Ks * pow(max(dot(H,N), 0.0), objectMaterial.shininess) * spot.intensity * attenuation;
	/*
	*/
	/*
	vec3 ambient = objectMaterial.Ka * spot.intensity * attenuation;
	vec3 diffuse =  objectMaterial.Kd * spot.intensity * dot(L, N) * attenuation;
	vec3 specular = objectMaterial.Ks * spot.intensity * attenuation;
	*/
	float noCompileOptimizeUniform = spot.material.shininess;

	return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
	vec3 L = normalize(spot.position.xyz - PositionInCamera);
	float distance = length(spot.position - vec4(PositionInCamera, 1.0));
	float attenuation = getAttenuation(distance);
	float theta = dot(-L, normalize(spot.direction));
	float angle = acos(theta);
	float spotAttenuation;

	if (angle < spot.innerCutoff) {
		spotAttenuation = 1.0;
	} else {
		float spotValue = smoothstep(cos(spot.cutoff),cos(spot.innerCutoff),cos(0));
		/*
		float spotDot = dot(-L, spot.direction);
		float spotValue = smoothstep(cos(spot.cutoff),
			cos(spot.innerCutoff),spotDot);
		*/

		spotAttenuation = pow(spotValue, spot.exponent);
	}
	attenuation *= spotAttenuation;
	FragColor = phong(L, attenuation);
	//FragColor = vec4(normalize(spot.direction)*0.5+0.5,1);
}
