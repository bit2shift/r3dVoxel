using namespace r3dVoxel;

class Monitor
{
	friend class Window;

private:
	void* m_handle;

public:
	static Array< Ref<Monitor> > getMonitors();
	static Ref<Monitor> getPrimary();
};
