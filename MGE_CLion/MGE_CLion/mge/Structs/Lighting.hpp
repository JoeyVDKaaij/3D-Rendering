#ifndef MGE_CLION_LIGHTING_HPP
#define MGE_CLION_LIGHTING_HPP

#include <glm/vec3.hpp>

struct Lighting
{
    float ambientIntensity = 1.0;
    glm::vec3 ambientLightColor = glm::vec3(1,1,1);
    glm::vec3 diffuseColor = glm::vec3(1,1,1);
    glm::vec3 lightColor = glm::vec3(1,1,1);
    float shininess = 256.0;
    glm::vec3 specularColor = glm::vec3(1,1,1);

    float constantAttenuation = 1.0;
    float linearAttenuation = 0.09;
    float quadraticAttenuation = 0.032;

    Lighting(float pAmbientIntensity,
             glm::vec3 pAmbientLightColor,
             glm::vec3 pDiffuseColor,
             glm::vec3 pLightColor,
             float pShininess,
             glm::vec3 pSpecularColor,
             float pConstantAttenuation,
             float pLinearAttenuation,
             float pQuadraticAttenuation);
};

#endif //MGE_CLION_LIGHTING_HPP
