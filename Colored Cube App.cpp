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
#include "Mountain - Nathan Snyder.h"
#include "Axes.h"
#include "GameObject.h"
#include "Obstacle.h"
#include "player.h"
#include <d3dx9math.h>
#include "constants.h"
#include "boost.h"
#include "boostObject.h"
#include "Ground_NickHalvorsen.h"
#include "Plane_NickHalvorsen.h"
#include "audio.h"
#include "Ship.h"
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
	
	Player player;
	Box redBox, mBox;
	Axes mAxes;
	Plane thePlane;
	Ground theGround;

	Mountain mt[6];	// Scenery
	Audio   *audio;
	Obstacle obstacles[NUM_OBSTACLES];
	Boost my_boost;
	boostObject boosts[NUM_BOOST];

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

	//Play startup music
	init_audio();
	int tune = rand() % 2;
	if (tune == 0)
		audio->playCue(THEME_MUSIC);
	else if (tune == 1)
		audio->playCue(THEME_MUSIC2);

	my_boost.init(md3dDevice, mTech);
	redBox.init(md3dDevice, mTech);
	mBox.init(md3dDevice, mTech);
	thePlane.init(md3dDevice, 1.0f, DARKBROWN);
	mAxes.init(md3dDevice, &mView, &mProj, mfxWVPVar, mTech);
	for(int i=0; i<6; ++i) {
		mt[i].init(md3dDevice, &mView, &mProj, mfxWVPVar, mTech);
	}
	mt[0].setScale(D3DXVECTOR3(75.0f, 50.0f, 1.0f));
	mt[0].setPosition(D3DXVECTOR3(0.0f, -3.0f, 300.0f));
	mt[1].setScale(D3DXVECTOR3(300.0f, 25.0f, 1.0f));
	mt[1].setPosition(D3DXVECTOR3(200.0f, -3.0f, 301.0f));
	mt[2].setScale(D3DXVECTOR3(55.0f, 40.0f, 1.0f));
	mt[2].setPosition(D3DXVECTOR3(-70.0f, -3.0f, 302.0f));
	mt[3].setScale(D3DXVECTOR3(55.0f, 20.0f, 1.0f));
	mt[3].setPosition(D3DXVECTOR3(370.0f, -3.0f, 302.0f));
	mt[4].setScale(D3DXVECTOR3(250.0f, 40.0f, 1.0f));
	mt[4].setPosition(D3DXVECTOR3(-200.0f, -3.0f, 301.0f));
	mt[5].setScale(D3DXVECTOR3(90.0f, 40.0f, 1.0f));
	mt[5].setPosition(D3DXVECTOR3(-370.0f, -3.0f, 302.0f));



	theGround.init(&thePlane, sqrt(1.0f), Vector3(0, -3, 0), Vector3(0, 0, 0), 0, 1);
	theGround.setMTech(mTech);
	player.init(&mBox, sqrt(2.0f), Vector3(0, 0, 5), Vector3(0, 0, 0), 0, 1);
	previousPlayerScale = 1.0f;
	player.setMTech(mTech);

	for (int i = 0; i < NUM_OBSTACLES; i++) {
		float randScale = randomScaleDistribution(generator);
		// spawn the obstacles evenly over the z direction. if they spawn too close to the player, hide them until they hit the back wall.
		obstacles[i].init(&redBox, sqrt(2.0f), Vector3(rand() % AREA_WIDTH - AREA_WIDTH / 2, 0, 1.0f * AREA_DEPTH/NUM_OBSTACLES*i), Vector3(0, 0, -OBSTACLE_SPEED), 0, randScale);
		obstacles[i].setMTech(mTech);
		if (obstacles[i].getPosition().z < AREA_DEPTH / 3)
			obstacles[i].setInActive(); 
	}
	for(int a = 0; a < NUM_BOOST; a++){
		//float randScale = randomDistribution(generator);
		boosts[a].init(&my_boost, sqrt(2.0f), Vector3(rand() % AREA_WIDTH - AREA_WIDTH / 2, 0, 1.0f * AREA_DEPTH/2/NUM_BOOST*a + AREA_DEPTH / 2), Vector3(0, 0, -OBSTACLE_SPEED), 0, 1.0f);
		boosts[a].setMTech(mTech);
	}

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
	// if(GetAsyncKeyState('A') & 0x8000)	mTheta -= 2.0f*dt;
	// if(GetAsyncKeyState('D') & 0x8000)	mTheta += 2.0f*dt;
	// if(GetAsyncKeyState('W') & 0x8000)	mPhi -= 2.0f*dt;
	// if(GetAsyncKeyState('S') & 0x8000)	mPhi += 2.0f*dt;

	// make the camera look more into the distance
	//mPhi = 1;

	if (GetAsyncKeyState(VK_ESCAPE)) exit(0);

	float turnSpeed = 100;
	float posChange = 0.0f;


	if (GetAsyncKeyState(VK_UP)) player.setVelocity(2.0f*player.getVelocity());
	if (GetAsyncKeyState(VK_DOWN))  player.setVelocity(.5f*player.getVelocity());

	if(player.getActiveState()) {
		if (GetAsyncKeyState(VK_LEFT)) {
			player.rotateZ(PI*0.15f,0.0f,1.5f);
			posChange  = + PLAYER_TURN_SPEED * dt;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			player.rotateZ(-PI*0.15f,0.0f,1.5f);
			posChange = - PLAYER_TURN_SPEED * dt;
		}
		distance += -obstacles[0].getVelocity().z*dt*0.5f;
	}


	if(abs(player.getScale()-previousPlayerScale) > 0.25f) {
		setScaleRange(player.getScale()-0.15, player.getScale()+0.75);
		previousPlayerScale = player.getScale();
	}
	for(int i=0;i<6;++i) {
		D3DXVECTOR3 tmpPosition = mt[i].getPosition();
		tmpPosition.x += posChange*0.5;
		mt[i].setPosition(tmpPosition);
	}

	// update obstacle positions
	for (int i = 0; i < NUM_OBSTACLES; i++) {
		obstacles[i].setPositionX(obstacles[i].getPosition().x + posChange);
		obstacles[i].setVelocity(Vector3(0, 0, -OBSTACLE_SPEED * player.getScale() / 2));
		obstacles[i].update(dt);
		if(obstacles[i].collided(&player)) {

			obstacles[i].setInActive();
			if(obstacles[i].getScale() >= player.getScale()) {	// obstacle is bigger
				player.decreaseScale(obstacles[i].getScale());
			} else {
				player.increaseScale(obstacles[i].getScale());
			}
		}
	}


	for (int i = 0; i < NUM_BOOST; i++) {
		boosts[i].setPositionX(boosts[i].getPosition().x + posChange);
		boosts[i].update(dt);
	}

	player.update(dt);
	


	// probably move this into obstacle.update ?
	for (int i = 0; i < NUM_OBSTACLES; i++) {
		if (obstacles[i].getPosition().z >= AREA_DEPTH) {
			float newScale = randomScaleDistribution(generator);
			obstacles[i].setScale(newScale);
		}
	}

	player.update(dt);
	theGround.update(dt);

	// Restrict the angle mPhi. 
	if( mPhi < 0.1f )	mPhi = 0.1f;
	if( mPhi > PI-0.1f)	mPhi = PI-0.1f;

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

	mClearColor = D3DXCOLOR(169.0f / 255.0f, 220.0f / 255.0f, 255.0f / 255.0f, 1.0f);

	// Restore default states, input layout and primitive topology 
	// because mFont->DrawText changes them.  Note that we can 
	// restore the default states by passing null.
	md3dDevice->OMSetDepthStencilState(0, 0);
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	md3dDevice->OMSetBlendState(0, blendFactors, 0xffffffff);
    md3dDevice->IASetInputLayout(mVertexLayout);
    
	mfxColorVar->SetInt(NO_CHANGE);
	//mAxes.draw();

	mWVP = theGround.getWorldMatrix()  *mView*mProj;
	mfxWVPVar->SetMatrix((float*)&mWVP);
	theGround.setMTech(mTech);
	theGround.draw();

	for(int i=0;i<6;++i) {
		mt[i].draw();
	}
   
	// set constants
	mWVP = mView*mProj;
	mfxWVPVar->SetMatrix((float*)&mWVP);


	mWVP = player.getWorldMatrix()  *mView*mProj;
	mfxWVPVar->SetMatrix((float*)&mWVP);
	mfxColorVar->SetInt(PLAYER);
	player.setMTech(mTech);
	player.draw();



	float playerScale = player.getScale();
	for (int i = 0; i < NUM_OBSTACLES; i++) {
		mWVP = obstacles[i].getWorldMatrix()  *mView*mProj;

		// Check whether it's bigger or smaller, color accordingly
		if(obstacles[i].getScale() >= playerScale) {		// Larger
			mfxColorVar->SetInt(LARGER);
		} else if (obstacles[i].getScale() + .2 >= playerScale) {
			mfxColorVar->SetInt(4);
		} else {	// Smaller
			mfxColorVar->SetInt(SMALLER);
		}

		/*
		// Tries to do a gradient based on how much bigger or smaller. Doesn't really work though
		
		mfxColorVar->SetInt(EXPERIMENTAL);

		// Calculate the gradient float
		float myDiff = 0.0f;
		if(obstacles[i].getScale() > playerScale) {
			myDiff = min(obstacles[i].getScale()-playerScale,1.0f);
		} else {
			myDiff = -min(playerScale-obstacles[i].getScale(),1.0f);
		}
		myDiff = (1.0f+myDiff) / 2.0f;
		mfxSlidingVar->SetFloat(myDiff);
		*/
		

		mfxWVPVar->SetMatrix((float*)&mWVP);
		obstacles[i].draw();
	}

	mfxColorVar->SetInt(NO_CHANGE);
	for(int i = 0; i < NUM_BOOST; i++){
		boosts[i].draw();
	}
	// We specify DT_NOCLIP, so we do not care about width/height of the rect.
	RECT R = {5, 5, 0, 0};
	mFrameStats.clear();



		std::wostringstream outs;   
		outs.precision(6);
		outs << L"Distance: " << static_cast<int>(distance/2);
		mFrameStats.append(outs.str());

	mFont->DrawText(0, mFrameStats.c_str(), -1, &R, DT_NOCLIP, BLACK);
	if(playerScale < 0.50f) {
		player.setScale(0.05f);
		player.setInActive();
		D3DXCOLOR fontColor(0.0f, 0.0f, 0.0f, 1.0f);
		RECT rectangle = {200, 200, 0, 0};
		Font->DrawText(0, L"Game Over", -1, &rectangle, DT_NOCLIP, fontColor);

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
