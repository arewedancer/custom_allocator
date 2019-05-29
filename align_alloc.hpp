#include <cstddef>
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
template <typename T> struct AlignAllocator {
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  static void *_addr;
  static std::size_t _size;
  inline explicit AlignAllocator() {};

  template <typename U> struct rebind { using other = AlignAllocator<U>; };

  template <class U> AlignAllocator(const AlignAllocator<U> &other) {
    _size = other._size;
    _addr = other._addr;
  };

  pointer address(reference x) const noexcept { return &x; }

  const_pointer address(const_reference x) const noexcept { return &x; }

  T *allocate(std::size_t n) {
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (n > 1) {
      size_t ex = n * sizeof(T);
      size_t pg = 1;
      while (1) {
        if (pg * pagesize / ex > 1)
          break;
        pg++;
      };
      posix_memalign((void **)&_addr, pagesize, pg * pagesize);
      _size = n * sizeof(T);
    } else {
      return reinterpret_cast<T *>(malloc(_size * sizeof(T)));
    };
    return reinterpret_cast<T *>(_addr);
  };
  void deallocate(T *p, std::size_t n) {
    if (n > 1)
      unprotect(p, n);
    free(p);
  };

  int read_protect() { return mprotect((void *)_addr, _size, PROT_READ); };

  int unprotect(void *p, std::size_t n) {
    return mprotect((void *)p, n * sizeof(T),
                    PROT_READ | PROT_WRITE | PROT_EXEC);
  };

  template <typename U, typename... Args>
  void construct(U *p, Args &&... args) {
    ::new (static_cast<void *>(p)) U(std::forward<Args>(args)...);
  }

  template <typename U> void destroy(U *p) { p->~U(); }
};

template <class T> void *AlignAllocator<T>::_addr = 0x0;
template <class T> std::size_t AlignAllocator<T>::_size = 0;

template <class T, class U>
bool operator==(const AlignAllocator<T> &, const AlignAllocator<U> &) {
  return false;
  ;
};
template <class T, class U>
bool operator!=(const AlignAllocator<T> &, const AlignAllocator<U> &) {
  return true;
};
