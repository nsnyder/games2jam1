//=======================================================================================
// boostObject.h by Michael Curtis (C) 2015 All Rights Reserved.
//=======================================================================================

#include "boostObject.h"
#include "boost.h"

void boostObject::init(Boost *b, float radius, Vector3 pos, Vector3 vel, float speed, float scale)
{
	boost = b;
	this->radius = radius;
	this->radius *= 1.01; //fudge factor
	position = pos;
	velocity = vel;
	this->speed = speed;
	this->scale = scale;
	radiusSquared = radius * radius;
}


void boostObject::draw()
{
	if (!active)
		return;
    D3D10_TECHNIQUE_DESC techDesc;
    mTech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        mTech->GetPassByIndex( p )->Apply(0);
        boost->draw();
    }
}