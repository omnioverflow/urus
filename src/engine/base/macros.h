#pragma once

//https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/c++/c++-dos-and-donts.md

#define DISALLOW_COPY(TypeName) \
	TypeName(const TypeName&) = delete; 


#define DISALLOW_ASSIGN(TypeName) \
	void operator=(const TypeName&) = delete
