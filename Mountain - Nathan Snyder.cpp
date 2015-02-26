//=======================================================================================
// Mountain.cpp by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================

#include "Mountain - Nathan Snyder.h"
#include "Vertex.h"

Mountain::Mountain()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}
 
Mountain::~Mountain()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Mountain::init(ID3D10Device* device,
				D3DXMATRIX* new_mView,
				D3DXMATRIX* new_mProj,
				ID3D10EffectMatrixVariable* new_mfxWVPVar,
				ID3D10EffectTechnique* new_mTech)
{
	mView = new_mView;
	mProj = new_mProj;
	mfxWVPVar = new_mfxWVPVar;
	md3dDevice = device;

	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	mTech = new_mTech;
 
	mNumVertices = 5;
	mNumFaces    = 3; // 2 per quad

	// Create vertex buffer
	
    Vertex vertices[] =
    {
		{D3DXVECTOR3(+1.0f, +0.0f, 0.0f), DARK_YELLOW_GREEN},	// Left Base
		{D3DXVECTOR3(-1.0f, +0.0f, 0.0f), DARK_YELLOW_GREEN},	// Right Base
		{D3DXVECTOR3(+0.0f, +2.0f, 0.0f), WHITE},	// Tip
		{D3DXVECTOR3(+.25f, +1.5f, 0.0f), DARKBROWN},
		{D3DXVECTOR3(-.25f, +1.5f, 0.0f), DARKBROWN}
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
		0, 1, 4,
		0, 4, 3,
		3, 4, 2
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

void Mountain::draw()
{
	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);

	D3DXMATRIX mTranslate;
	D3DXMatrixTranslation(&mTranslate, position.x, position.y, position.z);

	// Do the transforms, draw the line
	D3DXMATRIX mWVP = mScale*mTranslate*(*mView)*(*mProj);
	mfxWVPVar->SetMatrix((float*)&mWVP);

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