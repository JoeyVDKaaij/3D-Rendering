#include "RotatingByKeyBindsBehaviour.hpp"
#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>

RotatingByKeyBindsBehaviour::RotatingByKeyBindsBehaviour():AbstractBehaviour()
{
    //ctor
}

RotatingByKeyBindsBehaviour::~RotatingByKeyBindsBehaviour()
{
    //dtor
}

void RotatingByKeyBindsBehaviour::update(float pStep)
{
    //rotates 45� per second
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        _owner->rotate(pStep * glm::radians(45.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) );
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        _owner->rotate(pStep * glm::radians(-45.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) );
}
