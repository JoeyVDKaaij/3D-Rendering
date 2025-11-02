#include <iostream>
#include <string>

#include "../../glm.hpp"
#include "Assignment2Demo.h"
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
#include "../behaviours/RotatingBehaviour.hpp" //
#include "../behaviours/CameraOrbitBehaviour.hpp" //
#include "../behaviours/MovementBehaviour.hpp" //
#include "../behaviours/KeysBehaviour.hpp" //
#include "../util/DebugHud.hpp" //


Assignment2Demo::Assignment2Demo() : MGEDemo ()
{
}

void Assignment2Demo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment2Demo::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");
    Mesh* teapotF = Mesh::load (config::MGE_MODEL_PATH+"teapot_flat.obj");
    Mesh* suzannaS = Mesh::load (config::MGE_MODEL_PATH+"suzanna_smooth.obj");
    Mesh* marioMesh = Mesh::load (config::MGE_MODEL_PATH+"Mario.obj");
    Mesh* stoneMesh = Mesh::load (config::MGE_MODEL_PATH+"stone.obj");

    //MATERIALS

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
    AbstractMaterial* runicStoneMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"runicfloor.png"));
    AbstractMaterial* bricksMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"bricks.jpg"));
    AbstractMaterial* redMaterial = new ColorMaterial (glm::vec3(1,0,0));
    AbstractMaterial* blueMaterial = new ColorMaterial (glm::vec3(0,0,1));
    AbstractMaterial* greenMaterial = new ColorMaterial (glm::vec3(0,1,0));
    AbstractMaterial* landMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"land.jpg"));
    AbstractMaterial* marioMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"mario_skin.png"));
    AbstractMaterial* stoneMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"Stone.jpeg"));

    //SCENE SETUP

    //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,6,7));
    camera->setBehaviour(new CameraOrbitBehaviour());
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
    plane->scale(glm::vec3(5,5,5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(runicStoneMaterial);
    _world->add(plane);

    //add a spinning sphere
    GameObject* sphere = new GameObject ("sphere", glm::vec3(0,0,0));
    sphere->scale(glm::vec3(0.5,0.5,0.5));
    sphere->setMesh (sphereMeshS);
    sphere->setMaterial(bricksMaterial);
    sphere->setBehaviour (new RotatingBehaviour());
    plane->add(sphere);

    GameObject* floor = new GameObject ("floor", glm::vec3(0,0,-10));
    floor->scale(glm::vec3(5,5,5));
    floor->setMesh(planeMeshDefault);
    floor->setMaterial(landMaterial);
    floor->setBehaviour(new MovementBehaviour(1));
    _world->add(floor);

    GameObject* teapot = new GameObject ("teapot", glm::vec3(0.75,0.25,0));
    teapot->scale(glm::vec3(0.25,0.25,0.25));
    teapot->setMesh(teapotF);
    teapot->setMaterial(blueMaterial);
    floor->add(teapot);

    GameObject* suzanna = new GameObject ("Suzanna", glm::vec3(0,0.25,0));
    suzanna->scale(glm::vec3(0.25,0.25,0.25));
    suzanna->setMesh(suzannaS);
    suzanna->setMaterial(redMaterial);
//    suzanna->setBehaviour(new MovementBehaviour(1));
    floor->add(suzanna);

//    GameObject* mario = new GameObject ("Mario", glm::vec3(-0.75,0,0));
//    mario->scale(glm::vec3(0.15,0.15,0.15));
//    mario->setMesh(marioMesh);
//    mario->setMaterial(marioMaterial);
//    floor->add(mario);

    GameObject* stone = new GameObject ("stone", glm::vec3(-0.75,0,0));
    stone->scale(glm::vec3(0.005,0.005,0.005));
    stone->setMesh(stoneMesh);
    stone->setMaterial(stoneMaterial);
    floor->add(stone);

    // Get the camera orbit behaviour
    AbstractBehaviour* behaviour = camera->getBehaviour();
    CameraOrbitBehaviour* orbit = dynamic_cast<CameraOrbitBehaviour*>(behaviour);
    orbit->setObj(sphere);
    orbit->setDistance(10);
    orbit->rotate();

    std::cout << "Amount of child objects = " << plane->getChildCount() << std::endl;
}

void Assignment2Demo::_render() {
    AbstractGame::_render();
    //_updateHud();
}

void Assignment2Demo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    //_hud->setDebugInfo(debugInfo);
    //_hud->draw();
}

Assignment2Demo::~Assignment2Demo()
{
    //dtor
}
