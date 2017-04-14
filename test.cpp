#include <vector>
#include <iostream>
#include <memory>
#include <vector>
#include <ext/debug_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/mt_allocator.h>
#include "shm_allocator.hpp"
#define max 10000000
int main()
{
//std::vector<int, ShmAllocator<int> > test_vector;
//std::vector<int, __gnu_cxx::__pool_alloc<int> > test_vector;
//std::vector<int> test_vector;
std::vector<int, __gnu_cxx::__mt_alloc<int> > test_vector;
test_vector.reserve(max);
for (int i = 0; i < max; ++i )
	test_vector.push_back(i);

/*for (auto ele : test_vector)
{
	std::cout << ele << ",";
}
std::cout << std::endl;*/

};
