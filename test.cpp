#include <vector>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <ext/debug_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/mt_allocator.h>
#include "shm_allocator.hpp"
#include "sta_allocator.hpp"
#include "align_alloc.hpp"

#define max 100000
int main()
{
//std::vector<int, ShmAllocator<int> > test_vector;
//std::vector<int, __gnu_cxx::__pool_alloc<int> > test_vector;
//std::vector<int, StaAllocator<int> > test_vector;
std::vector<int, AlignAllocator<int> > test_vector;
//std::vector<int, __gnu_cxx::__mt_alloc<int> > test_vector;
test_vector.reserve(max);
for (int i = 0; i < max; ++i )
	test_vector.push_back(i);

test_vector.get_allocator().read_protect();
std::cout << test_vector[3] << std::endl;
test_vector[3] = 123;

};
