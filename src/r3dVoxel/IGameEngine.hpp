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
	 * Returns array of IMonitor, empty on failure
	 */
	virtual r3dVoxel::Array<r3dVoxel::IMonitor*> getAllMonitors() = 0;

	/* Returns the primary monitor or nullptr on failure */
	virtual r3dVoxel::IMonitor* getPrimaryMonitor() = 0;


	////////////////////////
	//// WINDOW SECTION ////
	////////////////////////

	virtual r3dVoxel::IView* createView(/* TODO add parameters */) = 0;

	//TODO add relevant methods
};
