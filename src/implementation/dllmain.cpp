#define R3V_EXPORT
#include "../r3dVoxel.hpp"

//OpenGL-related includes
#define GLEW_MX
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//C includes
#include <stdlib.h>

//C++ includes
#include <map>

//Memory management system
#include "MemMgr.hpp"

//////////////////////////////////////////
//// MOST IMPORTANT PIECE OF OOP CODE ////
//////////////////////////////////////////
void r3dVoxel::IClass::release() const
{
	delete this;
}

//Implementation headers
#include "CByteArray.hpp"
#include "CClassArray.hpp"
#include "CMonitor.hpp"
#include "CView.hpp"
#include "CGameEngine.hpp"
