/*
 * The most important interface of r3dVoxel
 */
class IGameEngine : public r3dVoxel::IClass
{
public:
	/////////////////////////
	//// MONITOR SECTION ////
	/////////////////////////

	/*
	 * Returns IClassArray of connected monitors
	 * Can be NULL if it fails
	 * Modifying its contents is discouraged
	 */
	virtual r3dVoxel::IClassArray<r3dVoxel::IMonitor>* getAllMonitors() = 0;

	/* Returns the primary monitor */
	virtual r3dVoxel::IMonitor* getPrimaryMonitor() = 0;

	/*
	 * Returns true if the monitor configuration has been changed
	 * Clears an internal flag when called
	 * Use this to poll for changes in connected monitors
	 */
	virtual bool monitorsHaveChanged() = 0;


	////////////////////////
	//// WINDOW SECTION ////
	////////////////////////

	virtual r3dVoxel::IView* createView() = 0;

	//TODO add relevant methods
};
