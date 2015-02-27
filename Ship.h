#ifndef SHIP_H
#define SHIP_H

#include "d3dUtil.h"
#include "Vertex.h"
#include "Box.h"

class Ship : public Box {
public:
	Ship(): mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0) {}
	~Ship() {
		ReleaseCOM(mVB);
		ReleaseCOM(mIB);
	}

	void init(ID3D10Device* device, D3DXCOLOR c, ID3D10EffectTechnique* new_mTech) {
		mTech = new_mTech;
		md3dDevice = device;
		mNumVertices = 5;
		mNumFaces    = 6;

		Vertex vertices[] = {
			{D3DXVECTOR3(+0.0f, -0.5f, 0.0f), WHITE},
			{D3DXVECTOR3(+0.0f, +0.5f, +0.0f), WHITE},
			{D3DXVECTOR3(+0.5f, +0.0f, +0.0f), WHITE},
			{D3DXVECTOR3(-0.5f, +0.0f, -0.5f), WHITE},
			{D3DXVECTOR3(-0.5f, +0.0f, +0.5f), WHITE}};

		D3D10_BUFFER_DESC vbd;
		vbd.Usage = D3D10_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Vertex) * mNumVertices;
		vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		D3D10_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = vertices;
		HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mVB));

		DWORD indices[] = {
			// top face
			1, 2, 3,
			1, 4, 2,

			// bottom face
			0, 3, 1,
			0, 1, 4,

			// back face
			1, 3, 0,
			1, 0, 4
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

void draw() {
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

	float getRadius() { return 1; }

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10EffectTechnique* mTech;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;
};


#endif