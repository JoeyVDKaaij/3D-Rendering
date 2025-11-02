#ifndef MGE_CLION_MOVEMENTBEHAVIOUR_HPP
#define MGE_CLION_MOVEMENTBEHAVIOUR_HPP

#include "AbstractBehaviour.hpp"
#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>

class MovementBehaviour : public AbstractBehaviour
{
public:
    MovementBehaviour(float pSpeed);
    virtual ~MovementBehaviour();

    virtual void update(float pStep);

private:
    float _speed = 1.0f;
    glm::vec3 NormalizedVec3(glm::vec3 vec3);

};

#endif //MGE_CLION_MOVEMENTBEHAVIOUR_HPP