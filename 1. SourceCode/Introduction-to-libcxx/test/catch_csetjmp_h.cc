#include "catch2/catch.hpp"

#include "libcxx/include/csetjmp"

#include <iostream>

omega::jmp_buf buf;

/*
typedef struct __JUMP_BUFFER
{
	unsigned long Ebp;
	unsigned long Ebx;
	unsigned long Edi;
	unsigned long Esi;
	unsigned long Esp;
	unsigned long Eip;
	unsigned long Registration;
	unsigned long TryLevel;
	unsigned long Cookie;
	unsigned long UnwindFunc;
	unsigned long UnwindData[6];
} _JUMP_BUFFER;
*/
// __declspec(noreturn)
// [[noreturn]]
__declspec(noreturn) void a(int count)
{
	std::cout << "a(" << count << ") called\n";
	omega::longjmp(buf, count+1);
}

TEST_CASE("setjmp", "[csetjmp]")
{
	volatile int count = 0;
	if (setjmp(buf) != 10) {
		a(++count);
	}
}
