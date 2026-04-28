#version 430 core
// https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
precision mediump float;

in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity; //Ia=Id=Is
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float shiness;

const float gamma = 2.2;
const float irradiPerp = 1.0;

out vec4 FragColor;

// https://www.mathematik.uni-marburg.de/~thormae/lectures/graphics1/code/WebGLShaderLightMat/ShaderLightMat.html
vec3 phongBRDF(vec3 lightDir, vec3 viewDir, vec3 normal, vec3 phongDiffuseCol, vec3 phongSpecularCol, float phongShininess) {
  vec3 color = phongDiffuseCol;
  vec3 reflectDir = reflect(-lightDir, normal);
  float specDot = max(dot(reflectDir, viewDir), 0.0);

  color += pow(specDot, phongShininess) * phongSpecularCol;
  return color;
}


void main()
{
  vec3 lightDir = normalize(vec3(LightPosition) - Position);
  vec3 viewDir = normalize(-Position);
  vec3 n = normalize(Normal);

  vec3 radiance = Ka.rgb;
  
  float irradiance = max(dot(lightDir, n), 0.0) * irradiPerp;
  if (irradiance > 0.0) {
    vec3 brdf = phongBRDF(lightDir, viewDir, n, Kd.rgb, Ks.rgb, shiness);
    radiance += brdf * irradiance * LightIntensity.rgb;
  }

  radiance = pow(radiance, vec3(1.0 / gamma) ); // gamma correction
  gl_FragColor.rgb = radiance;
  gl_FragColor.a = 1.0;
}