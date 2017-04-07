#include <vector>
#include <iostream>
#include <memory>
#include <vector>
//#include <ext/debug_allocator.h>
#include "shm_allocator.hpp"
int main()
{
std::vector<int, ShmAllocator<int> > test_vector;
test_vector.push_back(1);
test_vector.push_back(11);
test_vector.push_back(111);

for (auto ele : test_vector)
{
	std::cout << ele << ",";
}
std::cout << std::endl;

};
