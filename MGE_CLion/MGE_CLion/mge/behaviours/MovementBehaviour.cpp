#include "MovementBehaviour.hpp"
#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>

MovementBehaviour::MovementBehaviour(float pSpeed):AbstractBehaviour(),_speed(pSpeed)
{
    //ctor
}

MovementBehaviour::~MovementBehaviour()
{
    //dtor
}

void MovementBehaviour::update(float pStep)
{
    glm::vec3 velocity = glm::vec3(0,0,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity += glm::vec3(-1,0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity += glm::vec3(1,0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity += glm::vec3(0,0,-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity += glm::vec3(0,0,1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        velocity += glm::vec3(0,-1,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        velocity += glm::vec3(0,1,0);

    _owner->translate(NormalizedVec3(velocity) * _speed * pStep * 10.0f);
}

// TEMP normalized vec3 because I don't know how to implement this in the glm class
// Also I don't think glm::vec3 has this either
glm::vec3 MovementBehaviour::NormalizedVec3(glm::vec3 vec3)
{
    return glm::vec3(vec3.x / vec3.length(), vec3.y / vec3.length(), vec3.z / vec3.length());
}