#ifndef COLORMATERIAL_HPP
#define COLORMATERIAL_HPP

#include <GL/glew.h>
#include "AbstractMaterial.hpp"
#include "../Structs/Lighting.hpp"

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class ColorMaterial : public AbstractMaterial
{
    public:
        ColorMaterial(glm::vec3 pColor = glm::vec3(1,0,0));
        virtual ~ColorMaterial();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        virtual void setLighting(Lighting pLighting, glm::vec3 lightPosition, glm::vec3 cameraPosition) override;

        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
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
        static void _lazyInitializeShader();

        //this one is unique per instance of color material
        glm::vec3 _diffuseColor;
};

#endif // COLORMATERIAL_HPP
