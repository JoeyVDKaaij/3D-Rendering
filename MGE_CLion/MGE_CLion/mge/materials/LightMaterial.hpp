#ifndef LIGHTMATERIAL_HPP
#define LIGHTMATERIAL_HPP

#include <GL/glew.h>
#include "AbstractMaterial.hpp"
#include "../Structs/Lighting.hpp"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class LightMaterial : public AbstractMaterial
{
    public:
        LightMaterial (Texture* pDiffuseTexture);
        virtual ~LightMaterial ();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        virtual void setLighting(Lighting pLighting, glm::vec3 lightPosition, glm::vec3 cameraPosition) override;

        void setDiffuseTexture (Texture* pDiffuseTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix;
        static GLint _uDiffuseTexture;
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

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        Texture* _diffuseTexture;

        LightMaterial(const LightMaterial&);
        LightMaterial& operator=(const LightMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
