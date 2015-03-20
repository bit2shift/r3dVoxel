/*
 * An interoperable byte array
 */
class IByteArray : public r3dVoxel::IClass
{
public:
	/* Returns the length of this array */
	virtual unsigned length() const = 0;

	/*
	 * Returns pointer to byte in this array
	 * Note: returns &array[index % length]
	 */
	virtual void* at(unsigned index) const = 0;
};
