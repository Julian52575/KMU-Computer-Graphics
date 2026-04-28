#version 400

in vec3 Position;
in vec3 Normal;
uniform vec4 LightPosition;
uniform vec3 LightIntensity; //Ia=Id=Is
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float shiness;

out vec4 FragColor;

void main()
{
	vec3 N = normalize(Normal);
	vec3 L = normalize(vec3(LightPosition) - Position);
	vec3 V = normalize(-Position);
	vec3 R = reflect(-L, N);
	vec3 diffuse = Kd * LightIntensity * max(dot(N, L), 0.0);
	vec3 ambient = Ka * LightIntensity;
	vec3 specular = Ks * LightIntensity * pow(max(dot(R, V), 0.0), shiness);
	vec3 color = ambient + diffuse + specular;
	
	FragColor = vec4(color, 1.0);
}