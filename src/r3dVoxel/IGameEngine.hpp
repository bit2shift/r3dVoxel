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
	 */
	virtual const r3dVoxel::IByteArray* getAllMonitors() = 0;

	/* Returns the primary monitor or NULL on failure */
	virtual const r3dVoxel::IMonitor* getPrimaryMonitor() = 0;


	////////////////////////
	//// WINDOW SECTION ////
	////////////////////////

	virtual r3dVoxel::IView* createView(/* TODO add parameters */) = 0;

	//TODO add relevant methods
};
