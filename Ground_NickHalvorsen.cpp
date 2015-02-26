//=======================================================================================
// Ground.cpp by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Ground_NickHalvorsen.h"
#include "Plane_NickHalvorsen.h"

void Ground::init(Plane* p, float r, Vector3 pos, Vector3 vel, float sp, float s)
{
	plane = p;
	Box * b = new Box;
	GameObject::init(b, r, pos, vel, sp, s);
	/*radius = r;
	radius *= 1.01; //fudge factor
	position = pos;
	velocity = vel;
	speed = sp;
	scale = s;
	radiusSquared = radius * radius;*/
}


void Ground::draw()
{
	if (!active)
		return;
	D3D10_TECHNIQUE_DESC techDesc;
	getmTech()->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		getmTech()->GetPassByIndex(p)->Apply(0);
		plane->draw();
	}
}