//=======================================================================================
// Obstacle.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Obstacle.h"

void Obstacle::update(float dt) {
	GameObject::update(dt);
	if (this->getPosition().z < -20) {
		int x = rand() % AREA_WIDTH - AREA_WIDTH / 2;
		this->setPositionZ(AREA_DEPTH);
		this->setPositionX(x);
		this->setActive();
	}
}

void Obstacle::increaseScale(float collidedScale) {
	setScale(getScale()+collidedScale*.05);
}

void Obstacle::decreaseScale(float collidedScale) {
	setScale(getScale()-collidedScale);
}