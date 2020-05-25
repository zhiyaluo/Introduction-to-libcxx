#include "catch.hpp"

#include "libcxx\include\cerrno"

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <share.h>
#include <io.h>

TEST_CASE("_get_errno", "[cerrno]")
{
	errno_t err;
	int pfh;
	_sopen_s(&pfh, "nonexistent.file", _O_WRONLY, _SH_DENYNO, _S_IWRITE);
	_get_errno(&err);
	REQUIRE(ENOENT == err);
	//printf("errno = %d\n", err);
	//printf("fyi, ENOENT = %d\n", ENOENT);
}

TEST_CASE("_set_errno", "[cerrno]")
{
	errno_t err;
	err = 0;
	_set_errno(ENOENT);
	_get_errno(&err);
	REQUIRE(ENOENT == err);
}


