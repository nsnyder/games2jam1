
#include "GameObject.h"

GameObject::GameObject()
{
	radius = 0;
	speed = 0;
	active = true;
	Identity(&world);
}

GameObject::~GameObject()
{
	box = NULL;
}

void GameObject::draw()
{
	if (!active)
		return;
    D3D10_TECHNIQUE_DESC techDesc;
    mTech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        mTech->GetPassByIndex( p )->Apply(0);
        box->draw();
    }
}

void GameObject::init(Box *b, float radius, Vector3 pos, Vector3 vel, float speed, float scale)
{
	box = b;
	this->radius = radius;
	this->radius *= 1.01; //fudge factor
	position = pos;
	velocity = vel;
	this->speed = speed;
	this->scale = scale;
	radiusSquared = (scale*radius) * (scale*radius);
}

void GameObject::update(float dt)
{
	position += velocity*dt;
	Identity(&world);
	Matrix translate;
	Translate(&translate, position.x, position.y, position.z);
	Matrix scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, scale, scale, scale);
	world = scaleMatrix*translate;
}

bool GameObject::collided(GameObject *gameObject)
{
	Vector3 diff = position - gameObject->getPosition();
	float length = D3DXVec3LengthSq(&diff);
	float radii = radiusSquared + gameObject->getRadiusSquare();
	if (length <= radii)
		return true;
	return false;
}