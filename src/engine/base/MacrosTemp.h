#pragma once

//https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/c++/c++-dos-and-donts.md

#define DISALLOW_COPY(TypeName) \
	TypeName(const TypeName&) = delete; 


#define DISALLOW_ASSIGN(TypeName) \
	void operator=(const TypeName&) = delete

// Macros to fix unused result/variable warning
#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
#define UNUSED(x) x
#endif
