// -*- C++ -*-
//===--------------------------- __config ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

/*

synposis
synopsis

文件结构
	版本
	细节

分类方法
	针对某个编译器做大的分类
	针对某个共有的功能做分类

判断平台 platform
	_AIX, __APPLE__, __CYGWIN32__, __CYGWIN__, 
	__DragonFly__, __FreeBSD__, __gnu_linux, 
	hpux, __hpux, linux, __linux, __linux__, 
	__MACH__, __MINGW32__, __MINGW64__, 
	__NetBSD__, __OpenBSD__, _POSIX_IPV6, 
	_POSIX_MAPPED_FILES, _POSIX_SEMAPHORES,
	_POSIX_THREADS, _POSIX_VERSION, 
	sun, __sun, __SunOS, __sun__, __SVR4, __svr4__, 
	TARGET_IPHONE_SIMULATOR, TARGET_OS_EMBEDDED, TARGET_OS_IPHONE, TARGET_OS_MAC, 
	UNIX, unix, __unix, __unix__,
	WIN32, _WIN32, __WIN32, __WIN32__, WIN64, _WIN64, __WIN64, __WIN64__, WINNT, __WINNT, __WINNT__

判断编译器 detecting compilers
	__clang__, __GNUC__, __GNUG__, 
	__HP_aCC, __HP_cc, __IBMCPP__, __IBMC__, 
	__ICC, __INTEL_COMPILER, _MSC_VER, __PGI, __SUNPRO_C, __SUNPRO_CC, 

判断编译器版本 detecting compiler versions
	__clang_major__, __clang_minor__, __clang_patchlevel__, __clang_version__, 
	__GNUC_MINOR__, __GNUC_PATCHLEVEL__, __GNUC__, __GNUG__, 
	__HP_aCC, __HP_cc, __IBMCPP__, __IBMC__, __ICC, __INTEL_COMPILER, __INTEL_COMPILER_BUILD_DATE, 
	_MSC_BUILD, _MSC_FULL_VER, _MSC_VER, 
	__PGIC_MINOR__, __PGIC_PATCHLEVEL__, __PGIC__, 
	__SUNPRO_C, __SUNPRO_CC, __VERSION__, __xlC_ver__, __xlC__, __xlc__

常用语法
	#if 0
	#endif

	#ifdef 
	#endif

	#ifdef	
	#else
	#endif

	#if defined
	#else
	#endif
*/

#ifndef _LIBCPP_CONFIG
#define _LIBCPP_CONFIG

#ifndef _MSC_VER // explicit macro necessary because it is only defined below in this file
#pragma GCC system_header
#endif

// 计算GCC版本
#ifdef __GNUC__
#define _GNUC_VER (__GNUC__ * 100 + __GNUC_MINOR__)
#endif

#pragma region "LIBCXX 版本"

#define _LIBCPP_VERSION 1101

#define _LIBCPP_ABI_VERSION 1

#define _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_X##_LIBCPP_Y
#define _LIBCPP_CONCAT(_LIBCPP_X,_LIBCPP_Y) _LIBCPP_CONCAT1(_LIBCPP_X,_LIBCPP_Y)

#define _LIBCPP_NAMESPACE _LIBCPP_CONCAT(__,_LIBCPP_ABI_VERSION)

#pragma endregion

#pragma region "大小端"

#ifdef __LITTLE_ENDIAN__
#if __LITTLE_ENDIAN__
#define _LIBCPP_LITTLE_ENDIAN 1
#define _LIBCPP_BIG_ENDIAN    0
#endif  // __LITTLE_ENDIAN__
#endif  // __LITTLE_ENDIAN__

#ifdef __BIG_ENDIAN__
#if __BIG_ENDIAN__
#define _LIBCPP_LITTLE_ENDIAN 0
#define _LIBCPP_BIG_ENDIAN    1
#endif  // __BIG_ENDIAN__
#endif  // __BIG_ENDIAN__

#ifdef __FreeBSD__
# include <sys/endian.h>
#  if _BYTE_ORDER == _LITTLE_ENDIAN
#   define _LIBCPP_LITTLE_ENDIAN 1
#   define _LIBCPP_BIG_ENDIAN    0
# else  // _BYTE_ORDER == _LITTLE_ENDIAN
#   define _LIBCPP_LITTLE_ENDIAN 0
#   define _LIBCPP_BIG_ENDIAN    1
# endif  // _BYTE_ORDER == _LITTLE_ENDIAN
# ifndef __LONG_LONG_SUPPORTED
#  define _LIBCPP_HAS_NO_LONG_LONG
# endif  // __LONG_LONG_SUPPORTED
#endif  // __FreeBSD__

#ifdef _WIN32
#  define _LIBCPP_LITTLE_ENDIAN 1
#  define _LIBCPP_BIG_ENDIAN    0
// Compiler intrinsics (GCC or MSVC)
#  if (defined(_MSC_VER) && _MSC_VER >= 1400) \
   || (defined(__GNUC__) && _GNUC_VER > 403)
#    define _LIBCP_HAS_IS_BASE_OF
#  endif
#endif  // _WIN32

#ifdef __linux__
#  if defined(__GNUC__) && _GNUC_VER >= 403
#    define _LIBCP_HAS_IS_BASE_OF
#  endif
#endif

#ifdef __sun__
# include <sys/isa_defs.h>
# ifdef _LITTLE_ENDIAN
#   define _LIBCPP_LITTLE_ENDIAN 1
#   define _LIBCPP_BIG_ENDIAN    0
# else
#   define _LIBCPP_LITTLE_ENDIAN 0
#   define _LIBCPP_BIG_ENDIAN    1
# endif
#endif // __sun__

#if !defined(_LIBCPP_LITTLE_ENDIAN) || !defined(_LIBCPP_BIG_ENDIAN)
# include <endian.h>
# if __BYTE_ORDER == __LITTLE_ENDIAN
#  define _LIBCPP_LITTLE_ENDIAN 1
#  define _LIBCPP_BIG_ENDIAN    0
# elif __BYTE_ORDER == __BIG_ENDIAN
#  define _LIBCPP_LITTLE_ENDIAN 0
#  define _LIBCPP_BIG_ENDIAN    1
# else  // __BYTE_ORDER == __BIG_ENDIAN
#  error unable to determine endian
# endif
#endif  // !defined(_LIBCPP_LITTLE_ENDIAN) || !defined(_LIBCPP_BIG_ENDIAN)

#pragma endregion

#pragma region "WIN32"

#ifdef _WIN32

// only really useful for a DLL
#ifdef _LIBCPP_DLL // this should be a compiler builtin define ideally...
# ifdef cxx_EXPORTS
#  define _LIBCPP_HIDDEN
#  define _LIBCPP_FUNC_VIS __declspec(dllexport)
#  define _LIBCPP_TYPE_VIS __declspec(dllexport)
# else
#  define _LIBCPP_HIDDEN
#  define _LIBCPP_FUNC_VIS __declspec(dllimport)
#  define _LIBCPP_TYPE_VIS __declspec(dllimport)
# endif
#else
# define _LIBCPP_HIDDEN
# define _LIBCPP_FUNC_VIS
# define _LIBCPP_TYPE_VIS
#endif

#ifndef _LIBCPP_INLINE_VISIBILITY
# ifdef _MSC_VER
#  define _LIBCPP_INLINE_VISIBILITY __forceinline
# else // MinGW GCC and Clang
#  define _LIBCPP_INLINE_VISIBILITY __attribute__ ((__always_inline__))
# endif
#endif

#ifndef _LIBCPP_EXCEPTION_ABI
#define _LIBCPP_EXCEPTION_ABI _LIBCPP_TYPE_VIS
#endif

#ifndef _LIBCPP_ALWAYS_INLINE
# ifdef _MSC_VER
#  define _LIBCPP_ALWAYS_INLINE __forceinline
# endif
#endif

#endif // _WIN32

#pragma endregion "WIN32"

#pragma region "__has_attribute"

#ifndef _WIN32 //GCC

#ifndef __has_attribute
#define __has_attribute(__x) 0
#endif

#ifndef _LIBCPP_HIDDEN
#define _LIBCPP_HIDDEN __attribute__ ((__visibility__("hidden")))
#endif

#ifndef _LIBCPP_FUNC_VIS
#define _LIBCPP_FUNC_VIS __attribute__ ((__visibility__("default")))
#endif

#ifndef _LIBCPP_TYPE_VIS
#  if __has_attribute(type_visibility)
#    define _LIBCPP_TYPE_VIS __attribute__ ((__type_visibility__("default")))
#  else
#    define _LIBCPP_TYPE_VIS __attribute__ ((__visibility__("default")))
#  endif
#endif

#ifndef _LIBCPP_INLINE_VISIBILITY
#define _LIBCPP_INLINE_VISIBILITY __attribute__ ((__visibility__("hidden"), __always_inline__))
#endif

#ifndef _LIBCPP_EXCEPTION_ABI
#define _LIBCPP_EXCEPTION_ABI _LIBCPP_TYPE_VIS
#endif

#ifndef _LIBCPP_CANTTHROW
#define _LIBCPP_CANTTHROW __attribute__ ((__nothrow__))
#endif

#ifndef _LIBCPP_ALWAYS_INLINE
#define _LIBCPP_ALWAYS_INLINE  __attribute__ ((__visibility__("hidden"), __always_inline__))
#endif

#else
#define __has_attribute(__x) 0
#endif

#pragma endregion

#pragma region "__clang__ || __GNUC___ || _MSC_VER"

#if defined(__clang__)

#if __has_feature(cxx_alignas)
#  define _ALIGNAS_TYPE(x) alignas(x)
#  define _ALIGNAS(x) alignas(x)
#else
#  define _ALIGNAS_TYPE(x) __attribute__((__aligned__(__alignof(x))))
#  define _ALIGNAS(x) __attribute__((__aligned__(x)))
#endif

#if !__has_feature(cxx_alias_templates)
#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#endif

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#ifdef __linux__
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#else
typedef __char16_t char16_t;
typedef __char32_t char32_t;
#endif
#endif

#if !(__has_feature(cxx_exceptions))
#define _LIBCPP_NO_EXCEPTIONS
#endif

#if !(__has_feature(cxx_rtti))
#define _LIBCPP_NO_RTTI
#endif

#if !(__has_feature(cxx_strong_enums))
#define _LIBCPP_HAS_NO_STRONG_ENUMS
#endif

#if !(__has_feature(cxx_decltype))
#define _LIBCPP_HAS_NO_DECLTYPE
#endif

#if __has_feature(cxx_attributes)
#  define _LIBCPP_NORETURN [[noreturn]]
#else
#  define _LIBCPP_NORETURN __attribute__ ((noreturn))
#endif

#if !(__has_feature(cxx_defaulted_functions))
#define _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
#endif  // !(__has_feature(cxx_defaulted_functions))

#if !(__has_feature(cxx_deleted_functions))
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#endif  // !(__has_feature(cxx_deleted_functions))

#if !(__has_feature(cxx_lambdas))
#define _LIBCPP_HAS_NO_LAMBDAS
#endif

#if !(__has_feature(cxx_nullptr))
#define _LIBCPP_HAS_NO_NULLPTR
#endif

#if !(__has_feature(cxx_rvalue_references))
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

#if !(__has_feature(cxx_static_assert))
#define _LIBCPP_HAS_NO_STATIC_ASSERT
#endif

#if !(__has_feature(cxx_auto_type))
#define _LIBCPP_HAS_NO_AUTO_TYPE
#endif

#if !(__has_feature(cxx_access_control_sfinae)) || !__has_feature(cxx_trailing_return)
#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#endif

#if !(__has_feature(cxx_variadic_templates))
#define _LIBCPP_HAS_NO_VARIADICS
#endif

#if !(__has_feature(cxx_trailing_return))
#define _LIBCPP_HAS_NO_TRAILING_RETURN
#endif

#if !(__has_feature(cxx_generalized_initializers))
#define _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
#endif

#if __has_feature(is_base_of)
#  define _LIBCP_HAS_IS_BASE_OF
#endif

// Objective-C++ features (opt-in)
#if __has_feature(objc_arc)
#define _LIBCPP_HAS_OBJC_ARC
#endif

#if __has_feature(objc_arc_weak)
#define _LIBCPP_HAS_OBJC_ARC_WEAK
#define _LIBCPP_HAS_NO_STRONG_ENUMS
#endif

#if !(__has_feature(cxx_constexpr))
#define _LIBCPP_HAS_NO_CONSTEXPR
#endif

#if defined(__FreeBSD__) && (__ISO_C_VISIBLE >= 2011 || __cplusplus >= 201103L)
#define _LIBCPP_HAS_QUICK_EXIT
#define _LIBCPP_HAS_C11_FEATURES
#endif

#if (__has_feature(cxx_noexcept))
#  define _NOEXCEPT noexcept
#  define _NOEXCEPT_(x) noexcept(x)
#else
#  define _NOEXCEPT throw()
#  define _NOEXCEPT_(x)
#endif

#if __has_feature(underlying_type)
#  define _LIBCXX_UNDERLYING_TYPE(T) __underlying_type(T)
#endif

// Inline namespaces are available in Clang regardless of C++ dialect.
#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std {inline namespace _LIBCPP_NAMESPACE {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD std::_LIBCPP_NAMESPACE

namespace std {
  inline namespace _LIBCPP_NAMESPACE {
  }
}

#elif defined(__GNUC__)

#define _ALIGNAS(x) __attribute__((__aligned__(x)))
#define _ALIGNAS_TYPE(x) __attribute__((__aligned__(__alignof(x))))

#define _LIBCPP_NORETURN __attribute__((noreturn))

#if !__EXCEPTIONS
#define _LIBCPP_NO_EXCEPTIONS
#endif

#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#define _LIBCPP_HAS_NO_CONSTEXPR

#define _NOEXCEPT throw()
#define _NOEXCEPT_(x)

#ifndef __GXX_EXPERIMENTAL_CXX0X__

#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#define _LIBCPP_HAS_NO_DECLTYPE
#define _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define _LIBCPP_HAS_NO_NULLPTR
#define _LIBCPP_HAS_NO_STATIC_ASSERT
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_VARIADICS
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#define _LIBCPP_HAS_NO_ALWAYS_INLINE_VARIADICS

#else  // __GXX_EXPERIMENTAL_CXX0X__

#define _LIBCPP_HAS_NO_TRAILING_RETURN
#define _LIBCPP_HAS_NO_ALWAYS_INLINE_VARIADICS

#if _GNUC_VER < 403
#define _LIBCPP_HAS_NO_RVALUE_REFERENCES
#endif

#if _GNUC_VER < 403
#define _LIBCPP_HAS_NO_STATIC_ASSERT
#endif

#if _GNUC_VER < 404
#define _LIBCPP_HAS_NO_ADVANCED_SFINAE
#define _LIBCPP_HAS_NO_DECLTYPE
#define _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_VARIADICS
#define _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS
#endif  // _GNUC_VER < 404

#if _GNUC_VER < 406
#define _LIBCPP_HAS_NO_NULLPTR
#endif

#endif  // __GXX_EXPERIMENTAL_CXX0X__

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace std { namespace _LIBCPP_NAMESPACE {
#define _LIBCPP_END_NAMESPACE_STD  } }
#define _VSTD std::_LIBCPP_NAMESPACE

namespace std {
namespace _LIBCPP_NAMESPACE {
}
using namespace _LIBCPP_NAMESPACE __attribute__((__strong__));
}

#elif defined(_MSC_VER)

#if (_MSC_VER >= 1900)
// 这些属性在VS2019中都存在
//#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#define _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER
//#define _LIBCPP_HAS_NO_CONSTEXPR
//#define _LIBCPP_HAS_NO_UNICODE_CHARS
//#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define __alignof__ __alignof
#define _LIBCPP_NORETURN __declspec(noreturn)
#define _ALIGNAS(x) __declspec(align(x))
//#define _LIBCPP_HAS_NO_VARIADICS

//#define _NOEXCEPT throw()
//#define _NOEXCEPT_(x)
#define _NOEXCEPT noexcept
#define _NOEXCEPT_(x) noexcept

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace omega {
#define _LIBCPP_END_NAMESPACE_STD  }
#define _VSTD omega

namespace omega {
}
#else
#define _LIBCPP_HAS_NO_TEMPLATE_ALIASES
#define _LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER
#define _LIBCPP_HAS_NO_CONSTEXPR
#define _LIBCPP_HAS_NO_UNICODE_CHARS
#define _LIBCPP_HAS_NO_DELETED_FUNCTIONS
#define __alignof__ __alignof
#define _LIBCPP_NORETURN __declspec(noreturn)
#define _ALIGNAS(x) __declspec(align(x))
#define _LIBCPP_HAS_NO_VARIADICS

#define _NOEXCEPT throw()
#define _NOEXCEPT_(x)

#define _LIBCPP_BEGIN_NAMESPACE_STD namespace omega {
#define _LIBCPP_END_NAMESPACE_STD  }
#define _VSTD omega

namespace omega {
}
#endif

#endif // __clang__ || __GNUC___ || _MSC_VER

#pragma endregion

/*
// Severity	Code	Description	Project	File	Line	Suppression State
// Error(active)	E0084	invalid combination of type specifiers	libcxx3VS2019V2	X : \code\libcxx\libcxx3VS2019V2\libcxx3VS2019V2\libcxx\include\__config.h	402
// C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.22.27905\include\xkeycheck.h
#if defined(char16_t)
#define char16_t EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "char16_t". \
Enable warning C4005 to find the forbidden define.
#endif // char16_t
#if defined(char32_t)
#define char32_t EMIT WARNING C4005
#error The C++ Standard Library forbids macroizing the keyword "char32_t". \
Enable warning C4005 to find the forbidden define.
#endif // char32_t
*/
// 因为VS2019中char16_t和char32_t已经是关键字了，不能再重复定义了。
#ifdef _LIBCPP_HAS_NO_UNICODE_CHARS
typedef unsigned short char16_t;
typedef unsigned int   char32_t;
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS

// static_assert
#ifdef _LIBCPP_HAS_NO_STATIC_ASSERT

template <bool> struct __static_assert_test;
template <> struct __static_assert_test<true> {};
template <unsigned> struct __static_assert_check {};
#define static_assert(__b, __m) \
    typedef __static_assert_check<sizeof(__static_assert_test<(__b)>)> \
    _LIBCPP_CONCAT(__t, __LINE__)

#endif  // _LIBCPP_HAS_NO_STATIC_ASSERT

// decltype
#ifdef _LIBCPP_HAS_NO_DECLTYPE
#define decltype(x) __typeof__(x)
#endif

// constexpr
#ifdef _LIBCPP_HAS_NO_CONSTEXPR
#define _LIBCPP_CONSTEXPR
#else
#define _LIBCPP_CONSTEXPR constexpr
#endif

// =default
#ifdef _LIBCPP_HAS_NO_DEFAULTED_FUNCTIONS
#define _LIBCPP_DEFAULT {}
#else
#define _LIBCPP_DEFAULT = default;
#endif

// 不对齐
#ifdef __GNUC__
#define _NOALIAS __attribute__((__malloc__))
#else
#define _NOALIAS
#endif

/*
*/
// Fix: !!!经过测试不支持!!! 只是VS2019高亮错了，VS2019 已经支持 __has_feature 特性.
#if (_MSC_VER >= 1900)
#	define __has_feature(__x) 1
#   define _LIBCPP_EXPLICIT explicit
#else
#ifndef __has_feature
#define __has_feature(__x) 0
#endif

#if __has_feature(cxx_explicit_conversions)
#   define _LIBCPP_EXPLICIT explicit
#else
#   define _LIBCPP_EXPLICIT
#endif
#endif

// enum class
#ifdef _LIBCPP_HAS_NO_STRONG_ENUMS
#define _LIBCPP_DECLARE_STRONG_ENUM(x) struct _LIBCPP_TYPE_VIS x { enum __lx
#define _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x) \
    __lx __v_; \
    _LIBCPP_ALWAYS_INLINE x(__lx __v) : __v_(__v) {} \
    _LIBCPP_ALWAYS_INLINE explicit x(int __v) : __v_(static_cast<__lx>(__v)) {} \
    _LIBCPP_ALWAYS_INLINE operator int() const {return __v_;} \
    };
#else  // _LIBCPP_HAS_NO_STRONG_ENUMS
#define _LIBCPP_DECLARE_STRONG_ENUM(x) enum class _LIBCPP_TYPE_VIS x
#define _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(x)
#endif  // _LIBCPP_HAS_NO_STRONG_ENUMS

// args...
#ifndef _LIBCPP_EXTERN_TEMPLATE
#define _LIBCPP_EXTERN_TEMPLATE(...) extern template __VA_ARGS__;
#endif

// The versions of these functions with the _l suffix are 
// identical except that they use the locale parameter passed in instead of the current thread locale.
// _vsprintf_l
/*
int vsprintf(
   char *buffer,
   const char *format,
   va_list argptr
);
int _vsprintf_l(
   char *buffer,
   const char *format,
   locale_t locale,
   va_list argptr
);
*/
// _l 代表这些函数可以接受一个locale,而不是默认使用当前的locale
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(_WIN32) || defined(__sun__)
#define _LIBCPP_LOCALE__L_EXTENSIONS 1
#endif
#ifdef __FreeBSD__
#define _DECLARE_C99_LDBL_MATH 1
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
#define _LIBCPP_HAS_DEFAULTRUNELOCALE
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__sun__)
#define _LIBCPP_WCTYPE_IS_MASK
#endif

#pragma region "debug 开关"

#ifdef _LIBCPP_DEBUG2
#   if _LIBCPP_DEBUG2 == 0
#       define _LIBCPP_DEBUG_LEVEL 1
#   elif _LIBCPP_DEBUG2 == 1
#       define _LIBCPP_DEBUG_LEVEL 2
#   else
#       error Supported values for _LIBCPP_DEBUG2 are 0 and 1
#   endif
#endif

#ifdef _LIBCPP_DEBUG2
#   include <__debug>
#else
#   define _LIBCPP_ASSERT(x, m) ((void)0)
#endif

#pragma endregion

#endif  // _LIBCPP_CONFIG
