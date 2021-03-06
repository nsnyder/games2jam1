//=============================================================================
// Color Cube App.cpp by Frank Luna (C) 2008 All Rights Reserved.
//
// Demonstrates coloring.
//
// Controls:
//		'A'/'D'/'W'/'S' - Rotate 
//
//=============================================================================

#include <ctime>
#include <random>

#include "d3dApp.h"
#include "Box.h"
#include "Axes.h"
#include "GameObject.h"
#include <d3dx9math.h>
#include "constants.h"
#include "audio.h"
#include "Plane.h"
#include "Ground.h"
#include <sstream>

class ColoredCubeApp : public D3DApp
{
public:
	ColoredCubeApp(HINSTANCE hInstance);
	~ColoredCubeApp();
	void init_audio();
	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene(); 
	ID3DX10Font* Font;

private:
	void buildFX();
	void buildVertexLayouts();
	void setScaleRange(float low, float high);
 
private:
	
	Box mBox;
	Axes mAxes;
	Plane mPlane;
	Ground theGround;

	GameObject player;
	GameObject obstacles[OBSTACLE_COUNT];

	Audio   *audio;

	ID3D10Effect* mFX;
	ID3D10EffectTechnique* mTech;
	ID3D10InputLayout* mVertexLayout;
	ID3D10EffectMatrixVariable* mfxWVPVar;
	ID3D10EffectScalarVariable* mfxColorVar;
	ID3D10EffectScalarVariable* mfxSlidingVar;

	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	D3DXMATRIX mWVP;

	float mTheta;
	float mPhi;

	float previousPlayerScale;

	float distance;

	std::uniform_real_distribution<float> randomScaleDistribution;
	std::mt19937 generator;

	float totalTime;
	float proximityPoints;

	bool gameOver;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


	ColoredCubeApp theApp(hInstance);
	
	theApp.initApp();

	return theApp.run();
}

ColoredCubeApp::ColoredCubeApp(HINSTANCE hInstance)
: D3DApp(hInstance), mFX(0), mTech(0), mVertexLayout(0),
  mfxWVPVar(0), mTheta(0.0f), mPhi(PI*0.30f), randomScaleDistribution(0.1f, 2.25f)
{
	D3DXMatrixIdentity(&mView);
	D3DXMatrixIdentity(&mProj);
	D3DXMatrixIdentity(&mWVP); 
}

ColoredCubeApp::~ColoredCubeApp()
{
	if( md3dDevice )
		md3dDevice->ClearState();

	ReleaseCOM(mFX);
	ReleaseCOM(mVertexLayout);
}

void ColoredCubeApp::init_audio(){
	 audio = new Audio();
     audio->initialize();
}

void ColoredCubeApp::initApp()
{
	D3DApp::initApp();

	distance = 0.0f;

	D3DX10_FONT_DESC fd;
	fd.Height = 100;
	fd.Width = 0;
	fd.Weight = 0;
	fd.MipLevels = 1;
	fd.Italic = false;
	fd.CharSet = OUT_DEFAULT_PRECIS;
	fd.Quality = DEFAULT_QUALITY;
	fd.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

	wcscpy(fd.FaceName, L"Impact");

	D3DX10CreateFontIndirect(md3dDevice, &fd, &Font);

	buildFX();
	buildVertexLayouts();
	srand(time(0));

	init_audio();

	mBox.init(md3dDevice, mTech);
	mPlane.init(md3dDevice, 1, D3DXCOLOR(.1, .5, .4, 1));
	mAxes.init(md3dDevice, &mView, &mProj, mfxWVPVar, mTech);

	player.init(&mBox, 1.0f, Vector3(0.0f, -1.0f, DEPTH/2.0f+TRANSLATE),Vector3(0.0f,0.0f,0.0f),2.0f, 1.0f);
	player.setSpeed(PLAYER_SPEED);

	player.setMTech(mTech);
	srand(time(0));
	for(int i=0;i<OBSTACLE_COUNT;++i) {
		int x = rand() % WIDTH - WIDTH / 2;
		int z = rand() % DEPTH;
		obstacles[i].init(&mBox, 1.0f, Vector3(x, -1.0f, z+TRANSLATE),Vector3(0.0f,0.0f,0.0f),2.0f, 1.0f);
		obstacles[i].setMTech(mTech);
		obstacles[i].setScale(0.75);

		int dir = rand() % 4;
		Vector3 obstacleVelocity;

		switch (dir)
		{
		case 0: obstacleVelocity = Vector3(OBSTACLE_SPEED, 0, OBSTACLE_SPEED); break;
		case 1: obstacleVelocity = Vector3(-1 * OBSTACLE_SPEED, 0, OBSTACLE_SPEED); break;
		case 2: obstacleVelocity = Vector3(OBSTACLE_SPEED, 0, -1 * OBSTACLE_SPEED); break;
		case 3: obstacleVelocity = Vector3(-1 * OBSTACLE_SPEED, 0, -1 * OBSTACLE_SPEED); break;
		}

		obstacles[i].setVelocity(obstacleVelocity);
	}
	
	theGround.init(&mPlane, 1, Vector3(0, -2.0f, 0+TRANSLATE), Vector3(0, 0, 0), 0, GAME_SIZE);

	totalTime = 0;
	proximityPoints = 0;
	gameOver = false;
}

void ColoredCubeApp::onResize()
{
	D3DApp::onResize();

	float aspect = (float)mClientWidth/mClientHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, 0.75f*PI, aspect, 1.0f, 500.0f);
}

void ColoredCubeApp::updateScene(float dt)
{
	D3DApp::updateScene(dt);

	// Update angles based on input to orbit camera around box.
	 //if(GetAsyncKeyState('A') & 0x8000)	mTheta -= 2.0f*dt;
	 //if(GetAsyncKeyState('D') & 0x8000)	mTheta += 2.0f*dt;
	 //if(GetAsyncKeyState('W') & 0x8000)	mPhi -= 2.0f*dt;
	 //if(GetAsyncKeyState('S') & 0x8000)	mPhi += 2.0f*dt;

	 // simulates what happens when you hit a cube (collision detection not implemented yet)
	 //if (GetAsyncKeyState('G') & 0x8000) gameOver = true;

	 theGround.update(dt);

	 for (int i = 0; i < OBSTACLE_COUNT; i++)
	 {
		 Vector3 oldPos = obstacles[i].getPosition();
		 obstacles[i].update(dt);
		 if (abs(obstacles[i].getPosition().x) + obstacles[i].getScale() > GAME_SIZE)
		 {
			 obstacles[i].setPosition(oldPos);
			 obstacles[i].setVelocity(Vector3(obstacles[i].getVelocity().x * -1, obstacles[i].getVelocity().y, obstacles[i].getVelocity().z));
		 }
		 if (abs(obstacles[i].getPosition().z-TRANSLATE) + obstacles[i].getScale() > GAME_SIZE)
		 {
			 obstacles[i].setPosition(oldPos);
			 obstacles[i].setVelocity(Vector3(obstacles[i].getVelocity().x, obstacles[i].getVelocity().y, obstacles[i].getVelocity().z * -1));
		 }

		 if (obstacles[i].collided(&player) && totalTime > INVULN_TIME)
			 gameOver = true;
	 }



	 if (!gameOver)
	 {
		 int directionX = 0;
		 int directionZ = 0;

		 if (GetAsyncKeyState(VK_LEFT) & 0x8000)	directionX = -1;
		 if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	directionX = 1;
		 if (GetAsyncKeyState(VK_UP) & 0x8000)		directionZ = 1;
		 if (GetAsyncKeyState(VK_DOWN) & 0x8000)	directionZ = -1;

		 player.setVelocity(Vector3(player.getSpeed() * directionX, 0, player.getSpeed() * directionZ));


		 totalTime += dt;

		 for (int i = 0; i < OBSTACLE_COUNT; i++)
		 {
			 if (abs(player.getPosition().x - obstacles[i].getPosition().x) + abs(player.getPosition().z - obstacles[i].getPosition().z) < 5)
			 {
				 proximityPoints += dt * 6;
			 }
		 }
	 }
	 else // gameOver
	 {
		 // slow obstacles down for game over
		 for (int i = 0; i < OBSTACLE_COUNT; i++)
		 {
			 obstacles[i].setVelocity(Vector3(obstacles[i].getVelocity().x * .998, obstacles[i].getVelocity().y, obstacles[i].getVelocity().z * .998));

			 if (abs(obstacles[i].getVelocity().x) + abs(obstacles[i].getVelocity().y) + abs(obstacles[i].getVelocity().z) < .1)
				 obstacles[i].setVelocity(Vector3(0, 0, 0));
		 }

		 // make player shrink into nothingness
		 player.setScale(player.getScale() * .998); 
		 player.setVelocity(Vector3(player.getVelocity().x * .9995, player.getVelocity().y, player.getVelocity().z * .9995));

	 }

	 Vector3 oldPos = player.getPosition();

	 player.update(dt);

	 if (!gameOver)
	 {
		 if (abs(player.getPosition().x) + player.getScale() > GAME_SIZE || abs(player.getPosition().z-TRANSLATE) + player.getScale() > GAME_SIZE)
			 player.setPosition(oldPos);
	 }


	if (GetAsyncKeyState(VK_ESCAPE)) exit(0);

	mPhi = 0.4f;

	// Restrict the angle mPhi. 
	//if( mPhi < 0.1f )	mPhi = 0.1f;
	//if( mPhi > PI-0.1f)	mPhi = PI-0.1f;


	//if (mPhi != 0.1f) mPhi = 0.1f;

	// Convert Spherical to Cartesian coordinates: mPhi measured from +y
	// and mTheta measured counterclockwise from -z.
	float x =  5.0f*sinf(mPhi)*sinf(mTheta);
	float z = -5.0f*sinf(mPhi)*cosf(mTheta);
	float y =  5.0f*cosf(mPhi);

	// Build the view matrix.
	D3DXVECTOR3 pos(x, y, z);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &pos, &target, &up);

}

void ColoredCubeApp::drawScene()
{
	D3DApp::drawScene();

	mClearColor = D3DXCOLOR(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f);

	// Restore default states, input layout and primitive topology 
	// because mFont->DrawText changes them.  Note that we can 
	// restore the default states by passing null.
	md3dDevice->OMSetDepthStencilState(0, 0);
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	md3dDevice->OMSetBlendState(0, blendFactors, 0xffffffff);
    md3dDevice->IASetInputLayout(mVertexLayout);
    
	//mAxes.draw();

	mWVP = player.getWorldMatrix() * mView * mProj;
	mfxWVPVar->SetMatrix((float*)&mWVP);

	mfxColorVar->SetInt(-1);
	player.draw();

	for(int i=0;i<OBSTACLE_COUNT;++i) {
		mWVP = obstacles[i].getWorldMatrix() * mView * mProj;
		mfxWVPVar->SetMatrix((float*)&mWVP);

		if (totalTime < INVULN_TIME)
			mfxColorVar->SetInt(1);
		else
			mfxColorVar->SetInt(0);
		//obstacles[i].setMTech(mTech);
		obstacles[i].draw();
	}
	
	// how to draw
	//mWVP = myObject.getWorldMatrix()  *mView*mProj;
	//mfxWVPVar->SetMatrix((float*)&mWVP);
	//myObject.setMTech(mTech);
	//myObject.draw();

	mfxColorVar->SetInt(-1);
	mWVP = theGround.getWorldMatrix()  *mView*mProj;
	mfxWVPVar->SetMatrix((float*)&mWVP);
	theGround.setMTech(mTech);
	theGround.draw();

	// We specify DT_NOCLIP, so we do not care about width/height of the rect.
	RECT R = {5, 5, 0, 0};
	mFrameStats.clear();


	std::wostringstream outs;   
	outs.precision(3);
	outs << L"Time survived: " << totalTime << " seconds\nDanger Points (stay close to obstacles): " << static_cast<int>(proximityPoints);
	mFrameStats.append(outs.str());

	mFont->DrawText(0, mFrameStats.c_str(), -1, &R, DT_NOCLIP, WHITE);

	if (gameOver)
	{
		RECT rectangle = { 200, 200, 0, 0 };
		mFont->DrawText(0, L"Game Over", -1, &rectangle, DT_NOCLIP, WHITE);
	}

	mSwapChain->Present(0, 0);
}

void ColoredCubeApp::buildFX()
{
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
 
	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	hr = D3DX10CreateEffectFromFile(L"color.fx", 0, 0,
		"fx_4_0", shaderFlags, 0, md3dDevice, 0, 0, &mFX, &compilationErrors, 0);
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
			ReleaseCOM(compilationErrors);
		}
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX10CreateEffectFromFile", true);
	} 

	mTech = mFX->GetTechniqueByName("ColorTech");
	
	mfxWVPVar = mFX->GetVariableByName("gWVP")->AsMatrix();
	mfxColorVar = mFX->GetVariableByName("mode")->AsScalar();
	mfxSlidingVar = mFX->GetVariableByName("diff")->AsScalar();
}

void ColoredCubeApp::buildVertexLayouts()
{
	// Create the vertex input layout.
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
    D3D10_PASS_DESC PassDesc;
    mTech->GetPassByIndex(0)->GetDesc(&PassDesc);
    HR(md3dDevice->CreateInputLayout(vertexDesc, 2, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &mVertexLayout));
}

void ColoredCubeApp::setScaleRange(float low, float high) {
	randomScaleDistribution = std::uniform_real_distribution<float>(low, high);
}
