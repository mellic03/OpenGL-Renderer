#version 330 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out vec3 gEmission;


in vec2 TexCoords;
in vec3 FragPos;
in mat3 TBN;


struct Material {
  sampler2D diffuseMap, specularMap, emissionMap, normalMap;
  float spec_exponent;
};
uniform Material material;

uniform vec3 diffuseColor;

void main()
{
  gPosition = vec4(FragPos, 1.0);

  vec3 normal = texture(material.normalMap, TexCoords).rgb;
  normal = normal * 2.0 - 1.0; 
  normal = normalize(TBN * normal);
  gNormal = normal;
  
  gAlbedoSpec.rgb = diffuseColor;
  gAlbedoSpec.a = 1.0;//texture(material.specularMap, TexCoords).r;

  gEmission = texture(material.emissionMap, TexCoords).rgb;
}
