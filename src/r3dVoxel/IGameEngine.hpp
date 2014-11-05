/*
 * The most important interface of r3dVoxel
 */

class IGameEngine : public r3dVoxel::IClass
{
public:
	/////////////////////////
	//// MONITOR SECTION ////
	/////////////////////////

	/* Returns a NULL-terminated array of connected monitors */
	/* The array is persistent and is updated when changes occur */
	virtual r3dVoxel::IMonitor** getMonitors() = 0;

	/* Returns the primary monitor */
	virtual r3dVoxel::IMonitor* getPrimaryMonitor() = 0;


	//TODO add relevant methods
};
