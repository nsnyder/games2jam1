//=======================================================================================
// boostObject.h by Michael Curtis (C) 2015 All Rights Reserved.
//=======================================================================================

#ifndef boostObject_H
#define boostObject_H

#include "d3dUtil.h"
#include "GameObject.h"
#include "Box.h"
#include "boost.h"
class boostObject : public GameObject
{
public:
	void boostObject::init(Boost *b, float radius, Vector3 pos, Vector3 vel, float speed, float scale);
	void draw();
private:
	Boost *boost;

};

#endif // boostObject_H