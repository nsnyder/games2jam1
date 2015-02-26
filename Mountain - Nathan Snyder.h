//=======================================================================================
// Mountain.h by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#ifndef Mountain_H
#define Mountain_H

#include "d3dUtil.h"

class Mountain
{
public:

	Mountain();
	~Mountain();

	void init(ID3D10Device* device,
			  D3DXMATRIX* new_mView,
			  D3DXMATRIX* new_mProj,
			  ID3D10EffectMatrixVariable* new_mfxWVPVar,
			  ID3D10EffectTechnique* new_mTech);
	void draw();
	D3DXVECTOR3 getScale() { return scale; }
	void setScale(D3DXVECTOR3 scale) { this->scale = scale; }
	D3DXVECTOR3 getPosition() { return position; }
	void setPosition(D3DXVECTOR3 position) { this->position = position; }

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10EffectTechnique* mTech;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;

	D3DXMATRIX* mView;
	D3DXMATRIX* mProj;
	ID3D10EffectMatrixVariable* mfxWVPVar;

	D3DXVECTOR3 scale;
	D3DXVECTOR3 position;
};


#endif // Mountain_H