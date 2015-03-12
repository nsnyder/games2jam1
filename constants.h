#ifndef Constants_H
#define Constants_H

//Defines to make life easier

#define Vector3 D3DXVECTOR3
#define Matrix D3DXMATRIX
#define Identity D3DXMatrixIdentity
#define Translate D3DXMatrixTranslation
#define RotateX D3DXMatrixRotationX
#define RotateY D3DXMatrixRotationY
#define RotateZ D3DXMatrixRotationZ
#define ToRadian D3DXToRadian
#define ToDegree D3DXToDegree

const int GAME_SIZE = 10;

const int DEPTH = GAME_SIZE;
const int WIDTH = GAME_SIZE;

const float TRANSLATE = 7.5f;

const int OBSTACLE_COUNT = 6;
const int OBSTACLE_SPEED = 5;

const wchar_t WAVE_BANK[]  = L"audio\\Win\\MyWBank.xwb";
// SOUND_BANK must be location of .xsb file.
const wchar_t SOUND_BANK[] = L"audio\\Win\\MySBank.xsb";

const int PLAYER_SPEED = 10;

#endif

