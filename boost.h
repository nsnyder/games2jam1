//=======================================================================================
// Boost.h by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#ifndef Boost_H
#define Boost_H

#include "d3dUtil.h"

class Boost
{
public:

	Boost();
	~Boost();

	void init(ID3D10Device* device, ID3D10EffectTechnique* new_mTech);
	void draw();

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10EffectTechnique* mTech;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;
};


#endif // Boost_H
