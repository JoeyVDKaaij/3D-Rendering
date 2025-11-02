#include "Light.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "../materials/AbstractMaterial.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition):GameObject(pName, pPosition)
{}

Light::~Light() {
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

void Light::setLighting(float pAmbientIntensity, glm::vec3 pAmbientLightColor, glm::vec3 pDiffuseColor, glm::vec3 pLightColor, float pShininess, glm::vec3 pSpecularColor, float pConstantAttenuation, float pLinearAttenuation, float pQuadraticAttenuation)
{
    _lighting = Lighting(pAmbientIntensity, pAmbientLightColor, pDiffuseColor, pLightColor, pShininess, pSpecularColor, pConstantAttenuation, pLinearAttenuation, pQuadraticAttenuation);
}

void Light::update(float pStep)
{
    GameObject::update(pStep);

    RecursiveLighting(_world, _world, nullptr, _world->getMainCamera());
}

void Light::RecursiveLighting(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, Camera* camera) {
    LightingSelf(pMaterial == nullptr?pGameObject->getMaterial():pMaterial, camera);
    LightingChildren(pWorld, pGameObject, pMaterial, camera);
}

void Light::LightingSelf(AbstractMaterial* pMaterial, Camera* camera) {
    if (pMaterial != nullptr) pMaterial->setLighting(_lighting, getLocalPosition(), camera->getLocalPosition());
}

void Light::LightingChildren(World* pWorld, GameObject* pGameObject, AbstractMaterial* pMaterial, Camera* camera) {
    int childCount = pGameObject->getChildCount();
    if (childCount < 1) return;

    GameObject* child = nullptr;
    for (int i = 0; i < childCount; i++) {
        child = pGameObject->getChildAt(i);
        RecursiveLighting(pWorld, child, pMaterial, camera);
    }
}