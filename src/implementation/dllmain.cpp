#define R3V_EXPORT
#include "../r3dVoxel.hpp"

#define GLEW_MX
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <new>

//////////////////////////////////////////
//// MOST IMPORTANT PIECE OF OOP CODE ////
//////////////////////////////////////////
void r3dVoxel::IClass::release()
{
	delete this;
}

//Singleton, of sorts
r3dVoxel::IGameEngine* THE_GAME_ENGINE = 0;

//Implementation headers
#include "CMonitor.hpp"
#include "CView.hpp"
#include "CGameEngine.hpp"
