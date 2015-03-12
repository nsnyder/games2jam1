//=======================================================================================
// Plane.h by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#ifndef Plane_H
#define Plane_H

#include "d3dUtil.h"


class Plane
{
public:

	Plane();
	~Plane();

	void init(ID3D10Device* device, float scale);
	void init(ID3D10Device* device, float scale, D3DXCOLOR c);
	void draw();

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;
};


#endif // Plane_H
