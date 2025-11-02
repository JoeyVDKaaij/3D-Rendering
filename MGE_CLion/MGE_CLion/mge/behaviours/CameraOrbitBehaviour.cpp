#include "CameraOrbitBehaviour.hpp"
#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>


CameraOrbitBehaviour::CameraOrbitBehaviour():AbstractBehaviour()
{
	//ctor
}

CameraOrbitBehaviour::~CameraOrbitBehaviour()
{
	//dtor
}

void CameraOrbitBehaviour::update(float pStep)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (_onPressed)
        {
            _onPressed = false;
            _oldMousePosition = (sf::Vector2f)sf::Mouse::getPosition();
        }
        // Change orbit angle
        undoRotate();
        updateAngle(pStep);
        rotate();
    }
    else
    {
        _onPressed = true;
    }

    updateDistance(pStep);

    updateByObjPosition();
}

void CameraOrbitBehaviour::setObj(GameObject* pObj)
{
    _obj = pObj;
}

void CameraOrbitBehaviour::setDistance(float pDistance)
{
    _distance = pDistance;
}

void CameraOrbitBehaviour::updateByObjPosition()
{
    glm::vec3 objVec3 = _obj->getWorldPosition();
    float newX = _distance * cos(glm::radians(_angleX)) * sin(glm::radians(_angleY));
    float newY = _distance * sin(glm::radians(_angleX));
    float newZ = _distance * cos(glm::radians(_angleY)) * cos(glm::radians(_angleX));
    _owner->setLocalPosition(objVec3 + glm::vec3(newX, -newY, newZ));
}

void CameraOrbitBehaviour::rotate()
{
    _owner->rotate(glm::radians(_angleY), glm::vec3(0,1,0));
    _owner->rotate(glm::radians(_angleX), glm::vec3(1,0,0));
}

void CameraOrbitBehaviour::undoRotate()
{
    _owner->rotate(glm::radians(_angleX), glm::vec3(-1,0,0));
    _owner->rotate(glm::radians(_angleY), glm::vec3(0,-1,0));
}

void CameraOrbitBehaviour::updateAngle(float pStep)
{
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();
    sf::Vector2f mouseDifference = mousePos - _oldMousePosition;

    // Change += to -= or other way around to set rotation direction
    _angleX += mouseDifference.y * _angleYSpeed * pStep;
    _angleY -= mouseDifference.x * _angleXSpeed * pStep;

    if (_angleX > 45.0) _angleX = 45.0;
    if (_angleX < -45.0) _angleX = -45.0;

    _oldMousePosition = mousePos;
}

void CameraOrbitBehaviour::updateDistance(float pStep)
{
    float distanceVelocity = 0.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
        distanceVelocity -= 1.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
        distanceVelocity += 1.0;

    _distance += distanceVelocity * pStep * 10.0;
}