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
};

#endif // Obstacle_H