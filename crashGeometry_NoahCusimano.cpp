// crashGeometry cpp: This piece of geometry will be used as an effect when the player hits an object
// Created by Noah Cusimano

#include "crashGeometry_NoahCusimano.h"
#include "Vertex.h"

crashGeometry::crashGeometry()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
	
}
 
crashGeometry::~crashGeometry()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void crashGeometry::init(ID3D10Device* device,
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
 
	mNumVertices = 13;
	mNumFaces    = 8; // 2 per quad

	// Create vertex buffer
	
    Vertex vertices[] =
    {
		{D3DXVECTOR3(0.0f, .0f, .0f), DARK_YELLOW_GREEN},// origin is 0
		
		{D3DXVECTOR3(1.0f, 1.0f, 1.0f), WHITE},//Quadrant I
		{D3DXVECTOR3(1.0f, -1.0f, 1.0f), WHITE},//II
		{D3DXVECTOR3(-1.0f, -1.0f, 1.0f), WHITE},//III
		{D3DXVECTOR3(-1.0f, 1.0f, 1.0f), WHITE},//IV

		

		{D3DXVECTOR3(1.8f, 1.8f, -0.8f), RED},//index 5
		{D3DXVECTOR3(1.2f, 1.2f, -0.2f), RED},
		
		{D3DXVECTOR3(1.8f, -1.8f, -0.8f), RED},//index 7
		{D3DXVECTOR3(1.2f, -1.2f, -0.2f), RED},
		
		{D3DXVECTOR3(-1.8f, -1.8f, -0.8f), RED},//index 9
		{D3DXVECTOR3(-1.2f, -1.2f, -0.2f), RED},

		{D3DXVECTOR3(-1.8f, 1.8f, -0.8f), RED},//index 10
		{D3DXVECTOR3(-1.2f, 1.2f, -0.2f), RED}
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
		
		1,5,6,
		6,5,1,

		2,7,8,
		8,7,2,

		3,9,10,
		10,9,3,
		
		4,11,12,
		12,11,4,
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

void crashGeometry::draw()
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