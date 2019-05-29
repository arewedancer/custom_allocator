#include <vector>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <ext/debug_allocator.h>
#include <ext/pool_allocator.h>
#include <ext/mt_allocator.h>
#include "shm_allocator.hpp"
#include "sta_allocator.hpp"
#include "align_alloc.hpp"
#include "tsl/hopscotch_hash.h"
#include "tsl/hopscotch_map.h"
#include "utils.h"

#define max 10000
int main()
{
//std::vector<int, ShmAllocator<int> > test_vector;
//std::vector<int, __gnu_cxx::__pool_alloc<int> > test_vector;
//std::vector<int, StaAllocator<int> > test_vector;
//std::vector<int, AlignAllocator<int> > test_vector;
//std::vector<int, __gnu_cxx::__mt_alloc<int> > test_vector;
//test_vector.reserve(max);
//std::map<int, int, std::equal_to<int>, AlignAllocator<std::pair<const int, int>>> test_map;
	tsl::hopscotch_map<int, int, mod_hash<9>, std::equal_to<int>, AlignAllocator<std::pair<const int,int>>> test_map;
for (int i = 0; i < max; ++i )
{
		test_map.insert(std::pair<int,int>(i,i*3));
		//test_vector.push_back(i);
};
test_map.get_allocator().read_protect();
for(auto s : test_map )
{
	std::cout << s.first << ":" << s.second << std::endl;
};
test_map.get_allocator().read_protect();
test_map[2]=12;
//for (int i = 0; i < max; ++i )
//{
//std::cout << test_vector[i] << std::endl;
//std::cout << test_map[i] << std::endl;
//};
//test_vector[3] = 123;*/

};
