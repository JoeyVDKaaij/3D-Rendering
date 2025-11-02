#ifndef CAMERAORBITBEHAVIOUR_HPP
#define CAMERAORBITBEHAVIOUR_HPP

#include "AbstractBehaviour.hpp"
#include "../core/GameObject.hpp"
#include <SFML/Graphics.hpp>

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class CameraOrbitBehaviour : public AbstractBehaviour
{
	public:
		CameraOrbitBehaviour();
		virtual ~CameraOrbitBehaviour();

		virtual void update(float pStep);

        void setObj(GameObject* pObj);

		void setDistance(float pDistance);

        void rotate();

        void undoRotate();

    private:
        GameObject* _obj;
        float _angleX = -40;
        float _angleY = 0;
		float _angleXSpeed = 10;
		float _angleYSpeed = 10;
		sf::Vector2f _oldMousePosition = sf::Vector2f(0,0);
		bool _onPressed = true;
    	float _distance = 5;

        void updateByObjPosition();
		void updateAngle(float pStep);
		void updateDistance(float pStep);
};

#endif // CAMERAORBITBEHAVIOUR_HPP
