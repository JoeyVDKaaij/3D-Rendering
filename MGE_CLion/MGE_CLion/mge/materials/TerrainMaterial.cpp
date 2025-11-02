#include "../../glm.hpp"

#include "TerrainMaterial.hpp"
#include "../core/Texture.hpp"
#include "../core/Light.hpp"
#include "../core/World.hpp"
#include "../core/Mesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/ShaderProgram.hpp"
#include "../config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uModelMatrix = 0;
GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_uSplatMap = 0;
GLint TerrainMaterial::_uHeightTexture = 0;
GLint TerrainMaterial::_uDiffuse1Texture = 0;
GLint TerrainMaterial::_uDiffuse2Texture = 0;
GLint TerrainMaterial::_uDiffuse3Texture = 0;
GLint TerrainMaterial::_uDiffuse4Texture = 0;
GLint TerrainMaterial::_uAmbientIntensity = 0;
GLint TerrainMaterial::_uAmbientLightColor = 0;
GLint TerrainMaterial::_uDiffuseColor = 0;
GLint TerrainMaterial::_uLightPosition = 0;
GLint TerrainMaterial::_uLightColor = 0;
GLint TerrainMaterial::_uCameraPosition = 0;
GLint TerrainMaterial::_uShininess = 0;
GLint TerrainMaterial::_uSpecularColor = 0;
GLint TerrainMaterial::_uConstantAttenuation = 0;
GLint TerrainMaterial::_uLinearAttenuation = 0;
GLint TerrainMaterial::_uQuadraticAttenuation = 0;
GLint TerrainMaterial::_uLightingInScene = 0;

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;

TerrainMaterial::TerrainMaterial(Texture * pSplatMap, Texture* pHeightTexture, Texture* pDiffuse1Texture,
                                 Texture* pDiffuse2Texture, Texture* pDiffuse3Texture, Texture* pDiffuse4Texture)
                                 :_splatMap(pSplatMap),_heightTexture(pHeightTexture),
                                 _diffuse1Texture(pDiffuse1Texture),_diffuse2Texture(pDiffuse2Texture),
                                 _diffuse3Texture(pDiffuse3Texture),_diffuse4Texture(pDiffuse4Texture)
{
    _lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"terrain.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"terrain.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uModelMatrix = _shader->getUniformLocation("modelMatrix");
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uSplatMap = _shader->getUniformLocation("splatMap");
        _uHeightTexture = _shader->getUniformLocation("heightMap");
        _uDiffuse1Texture = _shader->getUniformLocation("diffuse1Texture");
        _uDiffuse2Texture = _shader->getUniformLocation("diffuse2Texture");
        _uDiffuse3Texture = _shader->getUniformLocation("diffuse3Texture");
        _uDiffuse4Texture = _shader->getUniformLocation("diffuse4Texture");
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
        _uLightingInScene = _shader->getUniformLocation("lightInScene");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void TerrainMaterial::setSplatMap (Texture* pSplatMap) {
    _splatMap = pSplatMap;
}

void TerrainMaterial::setHeightTexture (Texture* pHeightTexture) {
    _heightTexture = pHeightTexture;
}

void TerrainMaterial::setDiffuse1Texture (Texture* pDiffuseTexture) {
    _diffuse1Texture = pDiffuseTexture;
}

void TerrainMaterial::setDiffuse2Texture (Texture* pDiffuseTexture) {
    _diffuse2Texture = pDiffuseTexture;
}

void TerrainMaterial::setDiffuse3Texture (Texture* pDiffuseTexture) {
    _diffuse3Texture = pDiffuseTexture;
}

void TerrainMaterial::setDiffuse4Texture (Texture* pDiffuseTexture) {
    _diffuse4Texture = pDiffuseTexture;
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_splatMap) return;
    if (!_heightTexture) return;
    if (!_diffuse1Texture) return;
    if (!_diffuse2Texture) return;
    if (!_diffuse3Texture) return;
    if (!_diffuse4Texture) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TerrainMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
    glUniform1i (_uSplatMap, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _heightTexture->getId());
    glUniform1i (_uHeightTexture, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _diffuse1Texture->getId());
    glUniform1i (_uDiffuse1Texture, 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, _diffuse2Texture->getId());
    glUniform1i (_uDiffuse2Texture, 3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, _diffuse3Texture->getId());
    glUniform1i (_uDiffuse3Texture, 4);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, _diffuse4Texture->getId());
    glUniform1i (_uDiffuse4Texture, 5);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

void TerrainMaterial::setLighting(Lighting pLighting, glm::vec3 lightPosition, glm::vec3 cameraPosition)
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
    glUniform1i(_uLightingInScene, 1);
}