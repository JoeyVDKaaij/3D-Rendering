//
// Created by joey on 29/10/2025.
//

#include "Lighting.hpp"

Lighting::Lighting(float pAmbientIntensity, glm::vec3 pAmbientLightColor, glm::vec3 pDiffuseColor, glm::vec3 pLightColor, float pShininess, glm::vec3 pSpecularColor, float pConstantAttenuation, float pLinearAttenuation, float pQuadraticAttenuation)
{
    ambientIntensity = pAmbientIntensity;
    ambientLightColor = pAmbientLightColor;
    diffuseColor = pDiffuseColor;
    lightColor = pLightColor;
    shininess = pShininess;
    specularColor = pSpecularColor;
    constantAttenuation = pConstantAttenuation;
    linearAttenuation = pLinearAttenuation;
    quadraticAttenuation = pQuadraticAttenuation;
}