//=======================================================================================
// ground.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#ifndef Ground_H
#define Ground_H

#include "d3dUtil.h"
#include "GameObject.h"
#include "Plane_NickHalvorsen.h"

class Ground : public GameObject
{
private:

public:
	Plane* plane;
	bool active;

	void draw();
	void init(Plane *p, float r, Vector3 pos, Vector3 vel, float sp, float s);
};

#endif // Ground_H