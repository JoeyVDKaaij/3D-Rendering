#ifndef MGE_CLION_TERRAINMATERIAL_HPP
#define MGE_CLION_TERRAINMATERIAL_HPP

#include <GL/glew.h>
#include "AbstractMaterial.hpp"
#include "../Structs/Lighting.hpp"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TerrainMaterial : public AbstractMaterial
{
public:
    TerrainMaterial (Texture* pSplatMap, Texture* pHeightTexture, Texture* pDiffuse1Texture,
                     Texture* pDiffuse2Texture, Texture* pDiffuse3Texture, Texture* pDiffuse4Texture);
    virtual ~TerrainMaterial ();

    virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    void setSplatMap (Texture* pSplatMap);
    void setHeightTexture (Texture* pHeightTexture);
    void setDiffuse1Texture (Texture* pDiffuseTexture);
    void setDiffuse2Texture (Texture* pDiffuseTexture);
    void setDiffuse3Texture (Texture* pDiffuseTexture);
    void setDiffuse4Texture (Texture* pDiffuseTexture);

    virtual void setLighting(Lighting pLighting, glm::vec3 lightPosition, glm::vec3 cameraPosition) override;

protected:
private:
    static ShaderProgram* _shader;
    static void _lazyInitializeShader();

    //in this example we cache all identifiers for uniforms & attributes
    static GLint _uModelMatrix;
    static GLint _uMVPMatrix;
    static GLint _uSplatMap;
    static GLint _uHeightTexture;
    static GLint _uDiffuse1Texture;
    static GLint _uDiffuse2Texture;
    static GLint _uDiffuse3Texture;
    static GLint _uDiffuse4Texture;
    static GLint _uAmbientIntensity;
    static GLint _uAmbientLightColor;
    static GLint _uDiffuseColor;
    static GLint _uLightPosition;
    static GLint _uLightColor;
    static GLint _uCameraPosition;
    static GLint _uShininess;
    static GLint _uSpecularColor;
    static GLint _uConstantAttenuation;
    static GLint _uLinearAttenuation;
    static GLint _uQuadraticAttenuation;
    static GLint _uLightingInScene;

    static GLint _aVertex ;
    static GLint _aNormal;
    static GLint _aUV ;

    Texture* _splatMap;
    Texture* _heightTexture;
    Texture* _diffuse1Texture;
    Texture* _diffuse2Texture;
    Texture* _diffuse3Texture;
    Texture* _diffuse4Texture;

    TerrainMaterial(const TerrainMaterial&);
    TerrainMaterial& operator=(const TerrainMaterial&);

};

#endif //MGE_CLION_TERRAINMATERIAL_HPP
