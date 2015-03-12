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
	 * Query connected monitors
	 * Returns array of IMonitor or NULL on failure
	 * Modifying its contents is discouraged
	 */
	virtual r3dVoxel::IClassArray* getAllMonitors() = 0;

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

	virtual r3dVoxel::IView* createView(/* TODO add parameters */) = 0;

	//TODO add relevant methods
};
