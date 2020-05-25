#include "catch.hpp"

#include "libcxx\include\cfenv"

TEST_CASE("fegetenv", "[cfenv]")
{
	omega::feclearexcept(FE_ALL_EXCEPT);
	int r = omega::feraiseexcept(FE_UNDERFLOW | FE_DIVBYZERO);
	REQUIRE(r == 0);
	int e = omega::fetestexcept(FE_ALL_EXCEPT);
	REQUIRE((e & FE_DIVBYZERO) != 0);
	REQUIRE((e & FE_UNDERFLOW) != 0);
}

TEST_CASE("fesetround", "[cfenv]")
{
	omega::fesetround(FE_DOWNWARD);
	// cmath
	// nearbyint
}