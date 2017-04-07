#include <cstddef>
#include <sys/mman.h>
template <class T>
struct ShmAllocator {
	typedef T value_type;
	inline explicit ShmAllocator(){};
	template <class U> ShmAllocator(const ShmAllocator<U>& other){};
	T* allocate(std::size_t n){
		return reinterpret_cast<T*>(mmap(NULL,(n * sizeof (T)), PROT_READ|PROT_WRITE, MAP_ANONYMOUS,-1, 0)); 
	};
	void deallocate(T* p, std::size_t n)
	{
		munmap(p, n * sizeof(T)); 
	};
};
template <class T, class U>
bool operator==(const ShmAllocator<T>&, const ShmAllocator<U>&)
{
	return false;;
};
template <class T, class U>
bool operator!=(const ShmAllocator<T>&, const ShmAllocator<U>&)
{
	return true;
};

