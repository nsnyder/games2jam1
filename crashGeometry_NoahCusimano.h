// crashGeometry header: This piece of geometry will be used as an effect when the player hits an object
// Created by Noah Cusimano

#ifndef crashGeometry_H
#define crashGeometry_H

#include "d3dUtil.h"
#include "GameObject.h"

class crashGeometry : public GameObject
{
public:

	crashGeometry();
	~crashGeometry();

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


#endif // crashGeometry_H