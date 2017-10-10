#include "bloom_filter.hpp"

#include <r3dVoxel/r3vABI.hpp>

#include <iostream>
#include <map>

R3VAPI void test_bloom_filter()
{
	r3dVoxel::util::bloom_filter<std::map<char, const char*>> filter;

	filter.add('b');

	std::cout << "should be false for 'a': " << std::boolalpha << filter.test('a') << std::endl;
	std::cout << "should be true  for 'b': " << std::boolalpha << filter.test('b') << std::endl;

	std::cout << "removed 'b'? " << std::boolalpha << filter.remove('b') << std::endl;
	std::cout << "now it should be false: " << std::boolalpha << filter.test('b') << std::endl;
}
