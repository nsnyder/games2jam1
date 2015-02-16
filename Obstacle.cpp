//=======================================================================================
// Obstacle.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Obstacle.h"
#include "Vertex.h"

Obstacle::Obstacle()
{
}
 
Obstacle::~Obstacle()
{
}

void Obstacle::init(ID3D10Device* device,
				D3DXMATRIX* new_mView,
				D3DXMATRIX* new_mProj,
				ID3D10EffectMatrixVariable* new_mfxWVPVar,
				ID3D10EffectTechnique* new_mTech)
{
	mView = new_mView;
	mProj = new_mProj;
	mfxWVPVar = new_mfxWVPVar;
	md3dDevice = device;
	mTech = new_mTech;
	mBox.init(device, mTech);

	x = 0;
	y = 0;
	z = 0;
	scale = 0.2;
}

void Obstacle::draw()
{
    D3D10_TECHNIQUE_DESC techDesc;
    mTech->GetDesc( &techDesc );

	// Rotation in Y
	/*D3DXMATRIX mRotate;
	D3DXMatrixRotationY(&mRotate, D3DXToRadian(-90));
	D3DXMATRIX mWVP = (mRotate)*(*mView)*(*mProj);
	mfxWVPVar->SetMatrix((float*)&mWVP);
	mLine.setColor(RED);	// Z Axis
	mLine.draw();*/

	// R

	// S
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, scale, scale, scale);

	// T
	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, x, y, z);
	
	
	D3DXMATRIX mWVP = (mScale)*(mTranslate)*(*mView)*(*mProj);
	mfxWVPVar->SetMatrix((float*)&mWVP);

	mBox.draw();
}