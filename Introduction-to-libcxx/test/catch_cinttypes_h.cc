#include "catch2/catch.hpp"

#include "libcxx/include/cinttypes"

TEST_CASE("strtoimax", "[inttypes]")
{
	{
		auto str = "helloworld";
		char* p = NULL;
		auto ret = omega::strtoimax(str, &p, 36);
		REQUIRE(ret == 1767707668033969);
		REQUIRE(p == (&str[0] + strlen(str)));
	}

	{
		auto str = "hellotuvxworld";
		char* p = NULL;
		//01234569
		//abcdefghij
		//klmnopqrst
		//uvwxyz
		auto ret = omega::strtoimax(str, &p, 30);
		REQUIRE_FALSE(ret == 1767707668033969);
		REQUIRE_FALSE(p == (&str[0] + strlen(str)));
		REQUIRE(*p == 'u');
	}
}
