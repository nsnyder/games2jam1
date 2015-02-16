//=======================================================================================
// obstacle.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#ifndef Obstacle_H
#define Obstacle_H

#include "d3dUtil.h"
#include "Box.h"

class Obstacle
{
public:

	Obstacle();
	~Obstacle();

	void init(ID3D10Device* device,
			  D3DXMATRIX* new_mView,
			  D3DXMATRIX* new_mProj,
			  ID3D10EffectMatrixVariable* new_mfxWVPVar,
			  ID3D10EffectTechnique* new_mTech,
			  Box* new_mBox);

	void draw();

	float getX(){ return x; }
	float getY(){ return y; }
	float getZ(){ return z; }
	float getScale() { return scale; }

	void setX(float X){x = X;}
	void setY(float Y){y = Y;}
	void setZ(float Z){z = Z;}
	void setScale(float sc){ scale = sc; }

private:
	ID3D10Device* md3dDevice;
	Box* mBox;
	D3DXMATRIX* mView;
	D3DXMATRIX* mProj;
	ID3D10EffectMatrixVariable* mfxWVPVar;
	ID3D10EffectTechnique* mTech;

	float x;
	float y;
	float z;
	float scale;
};


#endif // Line_H