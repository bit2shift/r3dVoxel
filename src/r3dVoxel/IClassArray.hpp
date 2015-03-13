/*
 * An array for IClass objects
 */
class IClassArray : public r3dVoxel::IClass
{
public:
	/* Returns the length of this array */
	virtual unsigned length() = 0;

	/*
	 * Returns an element of this array
	 * Note: returns array[index % length]
	 * Hint: IMonitor* mon = static_cast<IMonitor*>(arr->at(i));
	 */
	virtual r3dVoxel::IClass*& at(unsigned index) = 0;
};
