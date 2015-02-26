//=======================================================================================
// Boost.cpp by Michael Curtis (C) 2008 All Rights Reserved.
//=======================================================================================


#include "boost.h"
#include "Vertex.h"

Boost::Boost()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}
 
Boost::~Boost()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Boost::init(ID3D10Device* device, ID3D10EffectTechnique* new_mTech)
{
	mTech = new_mTech;
	md3dDevice = device;
 
	mNumVertices = 6;
	mNumFaces    = 4; // 2 per quad

	// Create vertex buffer
	
    Vertex vertices[] =
    {
		{D3DXVECTOR3(0.0f, 1.0f, 0.0f), DARK_YELLOW_GREEN},
		{D3DXVECTOR3(-1.0f, 0.0f, 0.0f), GREEN},
		{D3DXVECTOR3(-1.0f, -1.0f, 0.0f), BLUE},
		{D3DXVECTOR3(0.0f, 0.0f, 0.0f), GREEN},
		{D3DXVECTOR3(1.0f, -1.0f, 0.0f), BLUE},
		{D3DXVECTOR3(1.0f, 0.0f, 0.0f), GREEN},
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
		
		0, 1, 3,
		1, 2, 3,

		3, 4, 5,
		5, 0, 3
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

void Boost::draw()
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