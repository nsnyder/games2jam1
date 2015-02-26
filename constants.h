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


const int NUM_OBSTACLES = 400;
const int NUM_BOOST = 100;
const int AREA_WIDTH = 600;
const int AREA_DEPTH = 600;

const int NO_CHANGE = -1;
const int PLAYER = 0;
const int LARGER = 1;
const int SMALLER = 2;
const int EXPERIMENTAL = 3;

const int OBSTACLE_SPEED = 40;
const int PLAYER_TURN_SPEED = 30;

const float ABSORPTION_RATE = 30.0f;

#endif

