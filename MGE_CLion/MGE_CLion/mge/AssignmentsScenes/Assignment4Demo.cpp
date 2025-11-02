#include <iostream>
#include <string>

#include "../../glm.hpp"
#include "Assignment4Demo.h"
#include "../materials/AbstractMaterial.hpp"
#include "../config.hpp"

#include "../core/Renderer.hpp" //
#include "../core/Mesh.hpp" //
#include "../core/World.hpp" //
#include "../core/Texture.hpp" //
#include "../core/Light.hpp" //
#include "../core/Camera.hpp"  //
#include "../core/GameObject.hpp" //
#include "../materials/ColorMaterial.hpp" //
#include "../materials/TextureMaterial.hpp" //
#include "../materials/TerrainMaterial.hpp" //
#include "../behaviours/RotatingBehaviour.hpp" //
#include "../behaviours/CameraOrbitBehaviour.hpp" //
#include "../behaviours/MovementBehaviour.hpp" //
#include "../behaviours/KeysBehaviour.hpp" //
#include "../util/DebugHud.hpp" //
#include "../materials/LightMaterial.hpp"


Assignment4Demo::Assignment4Demo() : MGEDemo ()
{
}

void Assignment4Demo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment4Demo::_initializeScene()
{
    //MESHES
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");

    // Create terrain mesh! Since storing 8196 * 8196 vertices is quite a lot,
    // we make the rest of the needed vertices in the vertex shader!
//    Mesh* terrainMesh = Mesh::load(config::MGE_MODEL_PATH+"plane_8192.obj");
    Mesh* terrainMesh = Mesh::loadTerrain(524, 524);

    //MATERIALS

    // We create the terrain material so we make use of the terrain shaders.
    AbstractMaterial* terrainMaterial = new TerrainMaterial (
            Texture::load (config::MGE_TEXTURE_PATH+"splatmap.png"),
            Texture::load(config::MGE_TEXTURE_PATH+"heightmap.png"),
            Texture::load(config::MGE_TEXTURE_PATH+"grass.jpg"),
            Texture::load(config::MGE_TEXTURE_PATH+"dirt.jpg"),
            Texture::load(config::MGE_TEXTURE_PATH+"stone.jpg"),
            Texture::load(config::MGE_TEXTURE_PATH+"snow.jpg"));

    AbstractMaterial* lightMaterial = new LightMaterial(Texture::load (config::MGE_TEXTURE_PATH+"bricks.jpg"));

    //SCENE SETUP

    //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,6,7));
    camera->setBehaviour(new CameraOrbitBehaviour());
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* floor = new GameObject ("floor", glm::vec3(0,0,0));
    floor->scale(glm::vec3(3,3,3));
    floor->setMesh(terrainMesh);
    floor->setMaterial(terrainMaterial);
    _world->add(floor);

    // Get the camera orbit behaviour
    AbstractBehaviour* behaviour = camera->getBehaviour();
    CameraOrbitBehaviour* orbit = dynamic_cast<CameraOrbitBehaviour*>(behaviour);
    orbit->setObj(floor);
    orbit->setDistance(10);
    orbit->rotate();

    // Light
    Light* light = new Light("light", glm::vec3(0,3,0));
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->setLighting(
            0.1,
            glm::vec3(1,1,1),
            glm::vec3(1,1,1),
            glm::vec3(1,1,1),
            2,
            glm::vec3(1,1,1),
            1.0,
            0.09,
            0.032
    );
    light->setBehaviour(new MovementBehaviour(25));
//    _world->registerLight(light);
    _world->add(light);

    std::cout << "Amount of child objects = " << _world->getChildCount() << std::endl;
}

void Assignment4Demo::_render() {
    AbstractGame::_render();
    //_updateHud();
}

void Assignment4Demo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    //_hud->setDebugInfo(debugInfo);
    //_hud->draw();
}

Assignment4Demo::~Assignment4Demo()
{
    //dtor
}
