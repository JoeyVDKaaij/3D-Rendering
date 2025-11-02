#include "../../glm.hpp"

#include "ColorMaterial.hpp"
#include "../config.hpp"
#include "../core/GameObject.hpp"
#include "../core/Mesh.hpp"
#include "../core/ShaderProgram.hpp"

ShaderProgram* ColorMaterial::_shader = NULL;

GLint ColorMaterial::_uAmbientIntensity = 0;
GLint ColorMaterial::_uAmbientLightColor = 0;
GLint ColorMaterial::_uDiffuseColor = 0;
GLint ColorMaterial::_uLightPosition = 0;
GLint ColorMaterial::_uLightColor = 0;
GLint ColorMaterial::_uCameraPosition = 0;
GLint ColorMaterial::_uShininess = 0;
GLint ColorMaterial::_uSpecularColor = 0;
GLint ColorMaterial::_uConstantAttenuation = 0;
GLint ColorMaterial::_uLinearAttenuation = 0;
GLint ColorMaterial::_uQuadraticAttenuation = 0;
GLint ColorMaterial::_uLightingInScene = 0;

ColorMaterial::ColorMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void ColorMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"color.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"color.fs");
        _shader->finalize();

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
    }
}

ColorMaterial::~ColorMaterial()
{
    //dtor
}

void ColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void ColorMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    _shader->use();

    //set the material color
    //glUniform3fv (_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));
    
    glUniform1f(_shader->getUniformLocation("lightIntensity"), 10.0f);

    glUniform3f(_shader->getUniformLocation("diffuseColor"), _diffuseColor.r, _diffuseColor.g, _diffuseColor.b);

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );

}

void ColorMaterial::setLighting(Lighting pLighting, glm::vec3 lightPosition, glm::vec3 cameraPosition)
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
