#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../../glm.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "../Structs/Lighting.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ) );
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;

		void setLighting(float pAmbientIntensity, glm::vec3 pAmbientLightColor, glm::vec3 pDiffuseColor, glm::vec3 pLightColor, float pShininess, glm::vec3 pSpecularColor, float pConstantAttenuation, float pLinearAttenuation, float pQuadraticAttenuation);

		virtual void update(float pStep) override;

	private:
		Lighting _lighting = Lighting(1,glm::vec3(1,1,1),glm::vec3(1,1,1),glm::vec3(1,1,1),1,glm::vec3(1,1,1), 1.0, 0.09, 0.032);
		void RecursiveLighting(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, Camera* camera);
		void LightingSelf(AbstractMaterial* pMaterial, Camera* camera);
		void LightingChildren(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, Camera* camera);
};

#endif // LIGHT_HPP
