#include "internal.hpp"

//TODO createView()

class CGameEngine : public r3dVoxel::IGameEngine
{
public:
	void Release()
	{
		//XXX game engine shutdown area

		glfwTerminate();
		delete this;
	}

	r3dVoxel::IMonitor** getMonitors()
	{
		//TODO what's missing here
		return 0;
	}

	r3dVoxel::IMonitor* getPrimaryMonitor()
	{
		//TODO the same
		return 0;
	}
};

R3VAPI r3dVoxel::IGameEngine* r3vInitialize()
{
	if(!glfwInit())
		return 0;

	//XXX idk, but can have other stuff in here

	return new CGameEngine();
}
