#version 400

uniform vec3 lightPos; //light position in world space
uniform vec3 viewPos;  //camera position in world space

out vec4 FragColors;

in vec3 position;
in vec3 normal;

struct Material {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
}; 
  
uniform Material material;

const vec3 lightColor = vec3(5.0, 5.0, 5.0);


void main()
{
   vec3 L = normalize(lightPos - position);
   vec3 V = normalize(viewPos - position);	
   vec3 N = normal;
   vec3 R = reflect(-L, N);

   vec3 ambient = material.ambientColor * lightColor;	

   // Diffuse
   vec3 norm = normalize(normal);
   vec3 lightDir = normalize(lightPos - position);
   vec3 diffuse = max(dot(N,L),0.0) * lightColor * material.diffuseColor;

   // Specular https://learnopengl.com/Lighting/Materials
   vec3 viewDir = normalize(viewPos - position);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = pow( max(dot(R,V),0.0), material.shininess) * lightColor * material.specularColor;

   FragColors = vec4(diffuse + specular + ambient, 1.0);
}