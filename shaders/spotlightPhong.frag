#version 400

in vec3 PositionInCamera;
in vec4 glPosition;
in vec3 Normal;
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
}; 
uniform Spot spot; 
const float constantAttenuation = 1.0; 
const float linearAttenuation = 0.01f; 
const float quadraticAttenuation = 0.001f;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float shiness;

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
	vec3 V = normalize(-vec3(PositionInCamera));
	vec3 ambient = Ka * spot.intensity * attenuation;
	vec3 diffuse =  Kd * spot.intensity * dot(L, N) * attenuation;
	vec3 specular = Ks * spot.intensity * attenuation;

	diffuse += shiness * 0.001;
	return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
	vec3 L = normalize(vec3(spot.position) - vec3(PositionInCamera));
	float distance = length(spot.position - vec4(PositionInCamera, 1.0));
	float attenuation = getAttenuation(distance);
	float theta = dot(-L, spot.direction);
	float angle = acos(theta);
	float spotAttenuation;

	if (angle < spot.innerCutoff) {
		spotAttenuation = 1.0;
	} else {
		float spotDot = dot(spot.cutoff, spot.innerCutoff);
		float spotValue = smoothstep(cos(spot.cutoff),
			cos(spot.innerCutoff),spotDot);

		spotAttenuation = pow(spotValue, spot.exponent);
	}
	attenuation *= spotAttenuation;
	FragColor = phong(L, attenuation);
}
