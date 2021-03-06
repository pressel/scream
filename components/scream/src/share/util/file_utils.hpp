#ifndef SCREAM_FILE_UTILS_HPP
#define  SCREAM_FILE_UTILS_HPP

#include <cstdio>
#include <sstream>
#include <memory>

#include "share/error_defs.hpp"

namespace scream {
namespace util {

struct FILECloser { void operator() (FILE* fh) { fclose(fh); } };
using FILEPtr = std::unique_ptr<FILE, FILECloser>;

template<typename T>
void write (const T* v, size_t sz, const FILEPtr& fid) {
  size_t nwrite = fwrite(v, sizeof(T), sz, fid.get());
  scream_throw_if(nwrite != sz, "write: nwrite = " << nwrite << " sz = " << sz);
}

template<typename T>
void read (T* v, size_t sz, const FILEPtr& fid) {
  size_t nread = fread(v, sizeof(T), sz, fid.get());
  scream_throw_if(nread != sz, "read: nread = " << nread << " sz = " << sz);
}

} // namespace util
} // namespace scream

#endif // SCREAM_FILE_UTILS_HPP
