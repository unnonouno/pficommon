// Copyright (c)2008-2011, Preferred Infrastructure Inc.
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
// 
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
// 
//     * Neither the name of Preferred Infrastructure nor the names of other
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef INCLUDE_GUARD_PFI_SYSTEM_MMAPPER_H_
#define INCLUDE_GUARD_PFI_SYSTEM_MMAPPER_H_

#include <utility>
#include <string>

#include "../lang/noncopyable.h"

namespace pfi {
namespace system {
namespace mmapper {

class mmapper : pfi::lang::noncopyable {
public:
  typedef char* iterator;
  typedef const char* const_iterator;

  mmapper() : ptr(NULL), length(0), fd(-1) {}
  ~mmapper() { close(); }

  char& operator[](size_t n) { return *(ptr + n); }
  const char& operator[](size_t n) const { return *(ptr + n); }
  char* begin() { return ptr; }
  const char* begin() const { return ptr; }
  char* end() { return ptr + length; }
  const char* end() const { return ptr + length; }
  const char* cbegin() const { return begin(); }
  const char* cend() const { return end(); }
  size_t size() const { return length; }
  bool is_open() const { return ptr; }

  int open(const std::string& filename);
  int close();

  void swap(mmapper& other) {
    std::swap(ptr, other.ptr);
    std::swap(length, other.length);
    std::swap(fd, other.fd);
  }

private:
  char* ptr;
  size_t length;
  int fd;
};

}
}
}

namespace std {
template <>
void swap(pfi::system::mmapper::mmapper& x, pfi::system::mmapper::mmapper& y)
{
  x.swap(y);
}
}

#endif // #ifndef INCLUDE_GUARD_PFI_SYSTEM_MMAPPER_H_
