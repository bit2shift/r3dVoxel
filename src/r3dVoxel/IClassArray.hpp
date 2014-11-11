/*
 * An array for IClass objects
 */
template<typename T>
class IClassArray : public r3dVoxel::IClass
{
public:
	/* Returns the length of this array */
	virtual unsigned length() = 0;

	/*
	 * Returns an element of this array
	 * Note: returns array[index % length]
	 */
	virtual T*& at(unsigned index) = 0;
};
