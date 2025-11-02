#ifndef MGE_CLION_ROTATINGBYKEYBINDSBEHAVIOUR_HPP
#define MGE_CLION_ROTATINGBYKEYBINDSBEHAVIOUR_HPP

#include "AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingByKeyBindsBehaviour : public AbstractBehaviour
{
public:
    RotatingByKeyBindsBehaviour();
    virtual ~RotatingByKeyBindsBehaviour();

    virtual void update(float pStep);

};


#endif //MGE_CLION_ROTATINGBYKEYBINDSBEHAVIOUR_HPP
