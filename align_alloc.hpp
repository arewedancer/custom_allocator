#include <cstddef>
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
template <class T>
struct AlignAllocator {
	typedef T value_type;
	T* _addr; std::size_t _size;
	inline explicit AlignAllocator(){};
	template <class U> AlignAllocator(const AlignAllocator<U>& other){};
	T* allocate(std::size_t n){
		//int pagesize = sysconf(_SC_PAGE_SIZE);
		int pagesize = 4096;
		_size = n * sizeof(T);
		posix_memalign((void**)&_addr, pagesize, n * sizeof(T));
		return reinterpret_cast<T*>(_addr);
		//return reinterpret_cast<T*>(alloca(n * sizeof(T))); 
	};
	void deallocate(T* p, std::size_t n)
	{
		//munmap(p, n * sizeof(T)); 
		unprotect();
		free(p);
	};
  int read_protect()
	{
		int ret = mprotect((void*)_addr, _size, PROT_READ);
		return ret;
	};
  int unprotect()
	{
		int ret = mprotect((void*)_addr, _size, PROT_READ|PROT_WRITE|PROT_EXEC);
		return ret;
	};
};
template <class T, class U>
bool operator==(const AlignAllocator<T>&, const AlignAllocator<U>&)
{
	return false;;
};
template <class T, class U>
bool operator!=(const AlignAllocator<T>&, const AlignAllocator<U>&)
{
	return true;
};

