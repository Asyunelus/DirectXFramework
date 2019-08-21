#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

#define CLASS_NAME L"BusanJjobBob"
#define WINDOW_NAME L"BusanJjobBob Game"

#define COLLISION_LAYER_NULL -1

#define not !
#define PIE 3.141592f
#define DAY .f * 86400.f
#define HOUR .f * 3600.f
#define MIN .f * 60.f

#define _TRY_START_ try {
#define _TRY_END_ } catch(...) {}

#ifdef _DEBUG
#define _SHOW_MASK
#endif

#define LAYER_PLAYER_UNIT 1
#define LAYER_PLAYER_AIRUNIT 2
#define LAYER_ENEMY_UNIT 3
#define LAYER_ENEMY_AIRUNIT 4
#define LAYER_ITEM 5
#define LAYER_UI 6

#define SAFE_DELETE(p) {if (p) {delete p;} (p) = NULL;}
#define CLASSNAME L"AsyuFramework_LOL"
#define APPNAME L"LOL"

#define SAFE_DELETE(p) {if (p) {delete p;} (p) = nullptr;}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] p;} p=nullptr;}
#define ANGLETOX(p) (cosf((p) / 180.f * PIE))
#define ANGLETOY(p) (sinf((p) / 180.f * PIE))
#define GETANGLE(x1, y1, x2, y2) (atan2f((y2) - (y1), (x2) - (x1)) * 180.f / PIE)

#include <deque>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <random>
#include <fstream>
#include <functional>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

#include "SingleInstance.h"
#include "CustomVertex.h"
#include "Texture.h"
#include "Rects.h"
#include "KeyManager.h"
#include "Time.h"
#include "Camera.h"

#include "Transform.h"
#include "Component.h"

#include "BoxCollider2D.h"
#include "LineCollider2D.h"

#include "TextureManager.h"
#include "Sprite2D.h"

#include "GameObject.h"

#include "ObjectManager.h"

#include "IScene.h"
#include "SceneManager.h"

#include "DirectX.h"

#include "Unit.h"