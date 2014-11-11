/*
 * An array for basic types
 */
template<typename T>
class IBasicArray : public r3dVoxel::IClass
{
public:
	/* Returns the length of this array */
	virtual unsigned length() = 0;

	/*
	 * Returns an element of this array
	 * Note: returns array[index % length]
	 */
	virtual T& at(unsigned index) = 0;
};
