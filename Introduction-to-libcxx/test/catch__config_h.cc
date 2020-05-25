#include "catch.hpp"

#include "__config.h"

// Tag names starting with non alphanumeric characters are reserved
//TEST_CASE("__config.h", "[__has_feature]")

TEST_CASE("clang__has_feature", "[__config.h]")
{
//#define has_feature(x) 0
	int x = 0;
	// 没有#include "__config.h"
	// warning C4067:  unexpected tokens following preprocessor directive - expected a newline
#if __has_feature(cxx_rvalue_references)
	x = 1;
#else
	x = 100;
#endif
	REQUIRE(x == 100);
}

TEST_CASE("defined", "[__config.h]")
{
	int x = 0;
#ifdef A
	x = 'a';
#elif defined B
	x = 'b';
#else
	x = 'c';
#endif
	REQUIRE(x == 'c');
}