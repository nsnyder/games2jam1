//=======================================================================================
// obstacle.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#ifndef Obstacle_H
#define Obstacle_H

#include "d3dUtil.h"
#include "GameObject.h"
#include "Box.h"

class Obstacle : public GameObject
{
public:
	void update(float dt);
	void increaseScale(float collidedScale);
	void decreaseScale(float collidedScale);
};

#endif // Obstacle_H