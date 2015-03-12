//=======================================================================================
// Box.cpp by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#include "Box.h"
#include "Vertex.h"
#include "constants.h"

Box::Box()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}
 
Box::~Box()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Box::init(ID3D10Device* device, ID3D10EffectTechnique* new_mTech)
{
	mTech = new_mTech;
	md3dDevice = device;
 
	mNumVertices = 8;
	mNumFaces    = 12; // 2 per quad

	// Create vertex buffer
	
    Vertex vertices[] =
    {
		{D3DXVECTOR3(-1.0f, -1.0f, -1.0f), RED},
		{D3DXVECTOR3(-1.0f, +1.0f, -1.0f), D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f)},
		{D3DXVECTOR3(+1.0f, +1.0f, -1.0f), D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f) },
		{D3DXVECTOR3(+1.0f, -1.0f, -1.0f), RED},
		{D3DXVECTOR3(-1.0f, -1.0f, +1.0f), RED},
		{D3DXVECTOR3(-1.0f, +1.0f, +1.0f), D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f) },
		{D3DXVECTOR3(+1.0f, +1.0f, +1.0f), D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f) },
		{D3DXVECTOR3(+1.0f, -1.0f, +1.0f), RED},
    };


    D3D10_BUFFER_DESC vbd;
	
    vbd.Usage = D3D10_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex) * mNumVertices;
    vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vertices;
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mVB));


	// Create the index buffer

	DWORD indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3, 
		4, 3, 7
	};

	D3D10_BUFFER_DESC ibd;
    ibd.Usage = D3D10_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof(DWORD) * mNumFaces*3;
    ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices;
    HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));
}

void Box::draw()
{
	D3D10_TECHNIQUE_DESC techDesc;
	mTech->GetDesc( &techDesc );
	for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		mTech->GetPassByIndex( p )->Apply(0);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		md3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
		md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
		md3dDevice->DrawIndexed(mNumFaces*3, 0, 0);
	}
}