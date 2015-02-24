
#include "GameObject.h"

GameObject::GameObject()
{
	curX = 0;
	curY = 0;
	curZ = 0;
	destinationX = 0;
	destinationY = 0;
	destinationZ = 0;
	dirX = 0;
	dirY = 0;
	dirZ = 0;
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

	// Rotation stuff
	if(dirX == 1) {
		if(curX < destinationX) {
			curX += speedX*dt;
		} else if(destinationX != returnX) {
			dirX = -1;
			destinationX = returnX;
		} else {
			dirX = 0;
		}
	} else if(dirX == -1) {
		if(curX > destinationX) {
			curX -= speedX*dt;
		} else if(destinationX != returnX) {
			dirX = 1;
			destinationX = returnX;
		} else {
			dirX = 0;
		}
	}

	if(dirY == 1) {
		if(curY < destinationY) {
			curY += speedY*dt;
		} else if(destinationY != returnY) {
			dirY = -1;
			destinationY = returnY;
		} else {
			dirY = 0;
		}
	} else if(dirY == -1) {
		if(curY > destinationY) {
			curY -= speedY*dt;
		} else if(destinationY != returnY) {
			dirY = 1;
			destinationY = returnY;
		} else {
			dirY = 0;
		}
	}

	if(dirZ == 1) {
		if(curZ < destinationZ) {
			curZ += speedZ*dt;
		} else if(destinationZ != returnZ) {
			dirZ = -1;
			destinationZ = returnZ;
		} else {
			dirZ = 0;
		}
	} else if(dirZ == -1) {
		if(curZ > destinationZ) {
			curZ -= speedZ*dt;
		} else if(destinationZ != returnZ) {
			dirZ = 1;
			destinationZ = returnZ;
		} else {
			dirZ = 0;
		}
	}
	

	Identity(&world);
	Matrix rotateXMatrix;
	RotateX(&rotateXMatrix, curX);
	Matrix rotateYMatrix;
	RotateY(&rotateYMatrix, curY);
	Matrix rotateZMatrix;
	RotateZ(&rotateZMatrix, curZ);
	Matrix translate;
	Translate(&translate, position.x, position.y, position.z);
	Matrix scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, scale, scale, scale);
	// Put in rotation
	world = scaleMatrix*rotateXMatrix*rotateYMatrix*rotateZMatrix*translate;
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

void GameObject::rotateX(float destination, float returnLocation, float speed) {
	destinationX = destination;
	returnX = returnLocation;
	speedX = speed;
	if(destination<curX) {
		dirX = -1;
	} else {
		dirX = 1;
	}
}
void GameObject::rotateY(float destination, float returnLocation, float speed) {
	destinationY = destination;
	returnY = returnLocation;
	speedY = speed;
	if(destination<curY) {
		dirY = -1;
	} else {
		dirY = 1;
	}
}
void GameObject::rotateZ(float destination, float returnLocation, float speed) {
	destinationZ = destination;
	returnZ = returnLocation;
	speedZ = speed;
	if(destination<curZ) {
		dirZ = -1;
	} else {
		dirZ = 1;
	}
}