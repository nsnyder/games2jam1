//=======================================================================================
// player.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#ifndef Player_H
#define Player_H

#include "d3dUtil.h"
#include "Box.h"

class Player
{
public:

	Player();
	~Player();

	void init(ID3D10Device* device,
			  D3DXMATRIX* new_mView,
			  D3DXMATRIX* new_mProj,
			  ID3D10EffectMatrixVariable* new_mfxWVPVar,
			  ID3D10EffectTechnique* new_mTech);

	void draw();

	float getX(){ return x; }
	float getY(){ return y; }
	float getZ(){ return z; }

private:
	ID3D10Device* md3dDevice;
	Box mBox;
	D3DXMATRIX* mView;
	D3DXMATRIX* mProj;
	ID3D10EffectMatrixVariable* mfxWVPVar;
	ID3D10EffectTechnique* mTech;

	float x;
	float y;
	float z;
};


#endif // Line_H