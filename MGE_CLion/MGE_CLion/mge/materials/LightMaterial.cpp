#include "../../glm.hpp"

#include "LightMaterial.hpp"
#include "../core/Texture.hpp"
#include "../core/Light.hpp"
#include "../core/World.hpp"
#include "../core/Mesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/ShaderProgram.hpp"
#include "../config.hpp"

ShaderProgram* LightMaterial::_shader = NULL;

GLint LightMaterial::_uMVPMatrix = 0;
GLint LightMaterial::_uDiffuseTexture = 0;
GLint LightMaterial::_uAmbientIntensity = 0;
GLint LightMaterial::_uAmbientLightColor = 0;
GLint LightMaterial::_uDiffuseColor = 0;
GLint LightMaterial::_uLightPosition = 0;
GLint LightMaterial::_uLightColor = 0;
GLint LightMaterial::_uCameraPosition = 0;
GLint LightMaterial::_uShininess = 0;
GLint LightMaterial::_uSpecularColor = 0;
GLint LightMaterial::_uConstantAttenuation = 0;
GLint LightMaterial::_uLinearAttenuation = 0;
GLint LightMaterial::_uQuadraticAttenuation = 0;

GLint LightMaterial::_aVertex = 0;
GLint LightMaterial::_aNormal = 0;
GLint LightMaterial::_aUV = 0;

LightMaterial::LightMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

LightMaterial::~LightMaterial() {}

void LightMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"light.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"light.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
        _uAmbientIntensity = _shader->getUniformLocation("ambientIntensity");
        _uAmbientLightColor = _shader->getUniformLocation("ambientLightColor");
        _uDiffuseColor = _shader->getUniformLocation("diffuseColor");
        _uLightPosition = _shader->getUniformLocation("lightPosition");
        _uLightColor = _shader->getUniformLocation("lightColor");
        _uCameraPosition = _shader->getUniformLocation("cameraPosition");
        _uShininess = _shader->getUniformLocation("shininess");
        _uSpecularColor = _shader->getUniformLocation("specularColor");
        _uConstantAttenuation = _shader->getUniformLocation("constantAttenuation");
        _uLinearAttenuation = _shader->getUniformLocation("linearAttenuation");
        _uQuadraticAttenuation = _shader->getUniformLocation("quadraticAttenuation");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void LightMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void LightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
//    if (pWorld->getLightCount() > 0) {
//        std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
//    }

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}



void LightMaterial::setLighting(Lighting pLighting, glm::vec3 lightPosition, glm::vec3 cameraPosition)
{
    _shader->use();

    glUniform1f(_uAmbientIntensity, pLighting.ambientIntensity);
    glUniform3f(_uAmbientLightColor, pLighting.ambientLightColor.x, pLighting.ambientLightColor.y, pLighting.ambientLightColor.z);
    glUniform3f(_uDiffuseColor, pLighting.diffuseColor.x, pLighting.diffuseColor.y, pLighting.diffuseColor.z);
    glUniform3f(_uLightPosition, lightPosition.x, lightPosition.y, lightPosition.z);
    glUniform3f(_uLightColor, pLighting.lightColor.x, pLighting.lightColor.y, pLighting.lightColor.z);
    glUniform3f(_uCameraPosition, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform1f(_uShininess, pLighting.shininess);
    glUniform3f(_uSpecularColor, pLighting.specularColor.x, pLighting.specularColor.y, pLighting.specularColor.z);
    glUniform1f(_uConstantAttenuation, pLighting.constantAttenuation);
    glUniform1f(_uLinearAttenuation, pLighting.linearAttenuation);
    glUniform1f(_uQuadraticAttenuation, pLighting.quadraticAttenuation);
}