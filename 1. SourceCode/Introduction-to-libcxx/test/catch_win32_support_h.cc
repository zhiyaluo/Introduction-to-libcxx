#include "catch.hpp"

#include "support/win32/support.h"

TEST_CASE("vasprintf", "[support.h]")
{
	auto f = [](char** buf, const char* fmt, ...) -> int
	{
		va_list ap;
		va_start(ap, fmt);
		auto ret = vasprintf(buf, fmt, ap);
		va_end(ap);
		return ret;
	};

	//char buf[1024] = { 0 };
	//char** buf = 0;
	char* buf = 0;

	f((char**)& buf, "%s", "TEST_CASE(\"win32 support\", \"[support.h]\")");

	auto s = "TEST_CASE(\"win32 support\", \"[support.h]\")";
	auto lf = strlen(buf);
	auto ls = strlen(s);

	REQUIRE(lf == ls);
	REQUIRE(strcmp(buf, "TEST_CASE(\"win32 support\", \"[support.h]\")" ) == 0);
}

TEST_CASE("asprintf", "[support.h]")
{
	char* buf = 0;
	
	asprintf(&buf, "%s%d", "Visual Studio ", 2019);

	auto s = "Visual Studio 2019";
	
	REQUIRE(strlen(s) == strlen(buf));
	REQUIRE(strcmp(s, buf) == 0);
}

TEST_CASE("mbsnrtowcs", "[support.h]")
{
	const char* src = "测试中文";	//只有这种形式的src才可以，不然访问src地址会出错
	//const char src[] = "测试中文";
	//const char *src = "\u6c34"; // \u6c34是水
	//const char8_t* src= u8"\u6c34"; // \u6c34是水
	wchar_t dst[1024] = { 0 };

	// en_US.utf8
	//setlocale(LC_ALL, "zh_CN.UTF-8");
	setlocale(LC_ALL, "zh_CN");

	mbstate_t ps = mbstate_t();
	memset(&ps, 0, sizeof(mbstate_t));
	// Exception thrown at 0x57B039B4 (ucrtbased.dll) in libcxx3VS2019V2.exe: 0xC0000005: 
	// Access violation reading location 0xCC00AECB. occurred
	// 访问src地址出错
	auto ret = mbsnrtowcs(dst, (const char**)&src, strlen(src), 1024, &ps);

	const wchar_t* x = L"测试中文";
	auto ld = wcslen(dst);
	auto lx = wcslen(x);

	REQUIRE(ld == lx);
	REQUIRE(wcscmp(dst, x) == 0);

	setlocale(LC_ALL, "");
}

TEST_CASE("wcsnrtombs", "[support.h]")
{
	//const wchar_t* src = L"support";
	const wchar_t* src = L"中文";
	char dst[1024] = { 0 };

	//setlocale(LC_ALL, "en_US.utf8");
	//setlocale(LC_ALL, "zh_CN.UTF-8");
	//setlocale(LC_ALL, "zh_CN.GB2312");

	setlocale(LC_ALL, "chs");
	mbstate_t ps;
	memset(&ps, 0, sizeof(mbstate_t));
	auto ret = wcsnrtombs(dst, (const wchar_t**)&src, wcslen(src), 1024, &ps);

	//const char* x = "support";
	const char* x = "中文";
	auto ld = strlen(dst);
	auto lx = strlen(x);

	REQUIRE(ld == lx);
	REQUIRE(strcmp(dst, x) == 0);

	setlocale(LC_ALL, "");
}

TEST_CASE("__builtin_popcount", "[support.h]")
{
	unsigned int x = 1;
	// 大于等于32时未定义行为
	for (auto i = 0; i < 64; ++i)
	{
		REQUIRE(__builtin_popcount(x << i) == 1);
	}
	// Severity	Code	Description	Project	File	Line	Suppression State
	// Warning	C26452	Arithmetic overflow : Left shift count is negative or greater than or equal 
	// to the operand size which is undefined behavior(io.3).libcxx3VS2019V2	
	// X : \CODE\LIBCXX\LIBCXX3VS2019V2\LIBCXX3VS2019V2\TEST\CATCH_WIN32_SUPPORT_H.CC	87
	//auto y = x << 33;
	//REQUIRE((x << 32) == 1);
}

TEST_CASE("__builtin_popcountl", "[support.h]")
{
	unsigned long x = 1;
	for (auto i = 0; i < 32; ++i)
	{
		REQUIRE(__builtin_popcountl(x << i) == 1);
	}
}

// 方括号放入""内
TEST_CASE("__builtin_popcountll", "[support.h]")
{
	unsigned long long x = 1;
	for (auto i = 0; i < 64; ++i)
	{
		REQUIRE(__builtin_popcountll(x << i) == 1);
	}
}

TEST_CASE("__builtin_ctz", "[support.h]")
{
	unsigned int x = 1;
	for (auto i = 0; i < 64; ++i)
	{
		// 到了32位时，x等于1
		REQUIRE(__builtin_ctz(x << i) == i % 32);
	}
}

TEST_CASE("__builtin_clz", "[support.h]")
{
	unsigned int x = 1 << 31;
	for (auto i = 0; i < 32; ++i)
	{
		REQUIRE(__builtin_clz(x >> i) == 31-i);
	}
	// 函数指针可以指向内联函数
	auto p = __builtin_clz;
	(*p)(1);
}
