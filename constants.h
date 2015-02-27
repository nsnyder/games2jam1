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


const wchar_t WAVE_BANK[]  = L"audio\\Win\\MyWBank.xwb";
// SOUND_BANK must be location of .xsb file.
const wchar_t SOUND_BANK[] = L"audio\\Win\\MySBank.xsb";

const char THEME_MUSIC[] = "theme";
const char THEME_MUSIC2[] = "music_full";
const char GREEN_CUBE[] = "obstacle_green";
const char YELLOW_CUBE[] = "obstacle_yellow";
const char RED_CUBE[] = "obstacle_red";

const int NUM_OBSTACLES = 400;
const int NUM_CRASH_OBJECTS = 10;
const int NUM_BOOST = 100;
const int AREA_WIDTH = 600;
const int AREA_DEPTH = 200;

const int NO_CHANGE = -1;
const int PLAYER = 0;
const int LARGER = 1;
const int SMALLER = 2;
const int EXPERIMENTAL = 3;

const int OBSTACLE_SPEED = 80;
const int PLAYER_TURN_SPEED = 30;

const float ABSORPTION_RATE = 30.0f;

#endif

