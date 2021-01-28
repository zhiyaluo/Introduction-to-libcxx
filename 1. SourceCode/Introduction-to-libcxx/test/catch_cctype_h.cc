#include "catch.hpp"

#include "libcxx\include\cctype"

TEST_CASE("isalnum", "[cctype]")
{
	// isalnum returns a nonzero value if either isalpha or isdigit is nonzero for c, 
	// that is, if c is within the ranges A - Z, a - z, or 0 - 9.
	for (auto i = 'a'; i <= 'z'; ++i)
	{
		REQUIRE(omega::isalnum(i));
	}

	for (auto i = 'A'; i <= 'Z'; ++i)
	{
		REQUIRE(omega::isalnum(i));
	}

	for (auto i = '0'; i <= '9'; ++i)
	{
		REQUIRE(omega::isalnum(i));
	}
}

TEST_CASE("isalpha", "[cctype]")
{ 
	//  isalpha returns a nonzero value if c is within the ranges A - Z or a - z.
	for (auto i = 'a'; i <= 'z'; ++i)
	{
		REQUIRE(omega::isalpha(i));
	}

	for (auto i = 'A'; i <= 'Z'; ++i)
	{
		REQUIRE(omega::isalpha(i));
	}
}

TEST_CASE("isblank", "[cctype]")
{
	//  isblank returns a nonzero value if c is a space character (0x20) or horizontal tab character (0x09).
	REQUIRE(omega::isblank(' '));
	REQUIRE(omega::isblank('\t'));
	//REQUIRE(omega::isblank('\r'));
	//REQUIRE(omega::isblank('\n'));

	setlocale(LC_ALL, "zh_CN");
	//_wsetlocale(LC_ALL, L"zh_CN.UTF-8");
	REQUIRE(omega::isblank('¡¡'));

	setlocale(LC_ALL, "");
}

TEST_CASE("isdigit", "[cctype]")
{
	// isdigit returns a nonzero value if c is a decimal digit (0 - 9).
	for (auto i = '0'; i <= '9'; ++i)
	{
		REQUIRE(omega::isdigit(i));
	}
}

TEST_CASE("isgraph", "[cctype]")
{
	// PRINTABLE
	// isgraph returns a nonzero value if c is a printable character other than a space.
	for (auto i = 33; i < 127; ++i)
	{
		REQUIRE(omega::isgraph(i));
	}
}

TEST_CASE("isprint", "[cctype]")
{
	// isprint returns a nonzero value if c is a printable character¡ªthis includes the space character (0x20 - 0x7E).
	for (auto i = 32; i < 127; ++i)
	{
		REQUIRE(omega::isprint(i));
	}
}

TEST_CASE("ispunct", "[cctype]")
{
	for (auto i = 33; i < 127; ++i)
	{
		if (!omega::isalnum(i))
		{
			REQUIRE(omega::ispunct(i));
		}

		if (!omega::ispunct(i))
		{
			REQUIRE(omega::isalnum(i));
		}
	}
}

TEST_CASE("islower", "[cctype]")
{
	for (auto i = 0; i < 127; ++i)
	{
		if (i >= 97 && i < 123)
			REQUIRE(omega::islower(i));
		else
			REQUIRE_FALSE(omega::islower(i));
	}
}

TEST_CASE("isupper", "[cctype]")
{
	for (auto i = 0; i < 127; ++i)
	{
		if (i >= 65 && i < 91)
			REQUIRE(omega::isupper(i));
		else
			REQUIRE_FALSE(omega::isupper(i));
	}
}

TEST_CASE("tolower", "[cctype]")
{
	for (auto i = 65; i < 91; ++i)
	{
		REQUIRE(tolower(i) == i + 32);
	}
}

TEST_CASE("toupper", "[cctype]")
{
	for (auto i = 97; i < 123; ++i)
	{
		REQUIRE(toupper(i) == i - 32);
	}
}

TEST_CASE("isxdigit", "[cctype]")
{
	for (auto i = 0; i < 127; ++i)
	{
		if ((i >= 48 && i < 58) || (i >= 65 && i < 71) || (i >= 97 && i < 103))
		{
			REQUIRE(isxdigit(i));
		}
		else
		{
			REQUIRE_FALSE(isxdigit(i));
		}
	}
}

TEST_CASE("iscntrl", "[cctype]")
{
	for (auto i = 0; i < 127; ++i)
	{
		if (!omega::isprint(i))
		{
			REQUIRE(omega::iscntrl(i));
		}
		if (!omega::iscntrl(i))
		{
			REQUIRE(omega::isprint(i));
		}
	}
}

TEST_CASE("isspace", "[cctype]")
{
	for (auto i = 0; i < 127; ++i)
	{
		if (i == '\t' || i == '\n' || i == '\v' || i == '\f' || i == '\r' || i == ' ')
		{
			REQUIRE(omega::isspace(i));
		}
		else
		{
			REQUIRE_FALSE(omega::isspace(i));
		}
	}
}
