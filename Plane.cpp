//=======================================================================================
// Plane.cpp by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#include "Plane.h"
#include "Vertex.h"

Plane::Plane()
	: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}

Plane::~Plane()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}
void Plane::init(ID3D10Device* device, float scale, D3DXCOLOR c)
{
	md3dDevice = device;

	mNumVertices = 4;
	mNumFaces = 2; // 2 per quad

	// Create vertex buffer
	Vertex vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), c },
		{ D3DXVECTOR3(-1.0f, -1.0f, +1.0f), c },
		{ D3DXVECTOR3(+1.0f, -1.0f, +1.0f), c },
		{ D3DXVECTOR3(+1.0f, -1.0f, -1.0f), c }
	};

	// Scale the Plane.
	for (DWORD i = 0; i < mNumVertices; ++i)
		vertices[i].pos *= scale;


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
		0, 2, 3
	};

	D3D10_BUFFER_DESC ibd;
	ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * mNumFaces * 3;
	ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));
}
void Plane::init(ID3D10Device* device, float scale)
{
	md3dDevice = device;

	mNumVertices = 4;
	mNumFaces = 2; // 2 per quad

	// Create vertex buffer
	Vertex vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), DARKBROWN },
		{ D3DXVECTOR3(-1.0f, -1.0f, +1.0f), DARKBROWN },
		{ D3DXVECTOR3(+1.0f, -1.0f, +1.0f), DARKBROWN },
		{ D3DXVECTOR3(+1.0f, -1.0f, -1.0f), DARKBROWN }
	};


	// Scale the Plane.
	for (DWORD i = 0; i < mNumVertices; ++i)
		vertices[i].pos *= scale;


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
		0, 2, 3
	};

	D3D10_BUFFER_DESC ibd;
	ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * mNumFaces * 3;
	ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));
}

void Plane::draw()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	md3dDevice->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(mNumFaces * 3, 0, 0);
}