//=======================================================================================
// player.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Player.h"
#include "Vertex.h"

Player::Player()
{
}
 
Player::~Player()
{
}

void Player::init(ID3D10Device* device,
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
	mBox.init(device, 1.0f);

	x = 0;
	y = 0;
	z = 0;
}

void Player::draw()
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

	D3DXMATRIX mTransform;


	
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        mTech->GetPassByIndex( p )->Apply(0);
        
		mBox.draw();
    }
}