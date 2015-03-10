/*
 * An interoperable byte array
 */
class IByteArray : public r3dVoxel::IClass
{
public:
	/* Returns the length of this array */
	virtual unsigned length() = 0;

	/* Returns a pointer to the beginning of the array */
	virtual void* pointer() = 0;
};
