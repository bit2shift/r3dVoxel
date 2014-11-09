/*
 * It's an array, usable between different C runtimes
 */
class IArray : public r3dVoxel::IClass
{
public:
	/* Returns the length of the array */
	virtual unsigned length() = 0;

	/* Returns the array's type size */
	virtual r3dVoxel::TypeInfo type() = 0;

	/* Returns a raw pointer to the element */
	virtual void* raw(unsigned index) = 0;

	/* Returns an object element, if the type is IClass */
	virtual r3dVoxel::IClass*& at(unsigned index) = 0;
};
