#include "catch2/catch.hpp"

#include "libcxx/include/type_traits"

// helper class:
TEST_CASE("integral_constant", "[type_traits]") {
    using namespace omega;

    integral_constant<bool, true> true_t;

    REQUIRE(true_t.value == true);
    REQUIRE(true_t.operator bool() == true);
    REQUIRE(static_cast<bool>(true_t) == true);
}

// helper traits
TEST_CASE("is_const", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_const<const int>::value == true);
    REQUIRE(is_const<int>::value == false);
}

TEST_CASE("is_volatile", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_volatile<volatile int>::value == true);
    REQUIRE(is_volatile<int>::value == false);
}

TEST_CASE("remove_const", "[type_traits]") {
    using namespace omega;

    REQUIRE(std::is_same<remove_const<const int>::type, int>::value == true);
}

TEST_CASE("remove_volatile", "[type_traits]") {
    using namespace omega;

    REQUIRE(std::is_same<remove_volatile<volatile int>::type, int>::value == true);
}

TEST_CASE("remove_cv", "[type_traits]") {
    using namespace omega;

    REQUIRE(std::is_same<remove_cv<volatile const int>::type, int>::value == true);
}

// -- type
TEST_CASE("is_void", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_void<void>::value == true);
    REQUIRE(is_void<const void>::value == true);
    REQUIRE(is_void<volatile const void>::value == true);

    REQUIRE(is_void<int>::value == false);
}

TEST_CASE("__is_nullptr_t", "[type_traits]") {
    using namespace omega;

    REQUIRE(__is_nullptr_t<std::nullptr_t>::value == true);
    //REQUIRE(__is_nullptr_t<NULL>::value == true);
    //REQUIRE(__is_nullptr_t<nullptr>::value == true);

    REQUIRE(__is_nullptr_t<int>::value == false);
}

TEST_CASE("is_integral", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_integral<bool>::value == true);
    REQUIRE(is_integral<char>::value == true);
    REQUIRE(is_integral<signed char>::value == true);
    REQUIRE(is_integral<unsigned char>::value == true);
    REQUIRE(is_integral<wchar_t>::value == true);

    REQUIRE(is_integral<char16_t>::value == true);
    REQUIRE(is_integral<char32_t>::value == true);

    REQUIRE(is_integral<short>::value == true);
    REQUIRE(is_integral<unsigned short>::value == true);
    REQUIRE(is_integral<int>::value == true);
    REQUIRE(is_integral<unsigned int>::value == true);
    REQUIRE(is_integral<long>::value == true);
    REQUIRE(is_integral<unsigned long>::value == true);
    REQUIRE(is_integral<long long>::value == true);
    REQUIRE(is_integral<unsigned long long>::value == true);

    struct S {};
    REQUIRE(is_integral<S>::value == false);
    REQUIRE(is_integral<std::string>::value == false);
    REQUIRE(is_integral<float>::value == false);
    REQUIRE(is_integral<double>::value == false);
    REQUIRE(is_integral<long double>::value == false);
}

TEST_CASE("is_floating_point", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_floating_point<float>::value == true);
    REQUIRE(is_floating_point<double>::value == true);
    REQUIRE(is_floating_point<long double>::value == true);
    REQUIRE(is_floating_point<int>::value == false);
}

TEST_CASE("is_array", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_array<float[]>::value == true);
    REQUIRE(is_array<float[1]>::value == true);
    //int x;
    //REQUIRE(is_array<float[x]>::value == true);
    REQUIRE(is_array<int>::value == false);
}

TEST_CASE("is_pointer", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_pointer<float[]>::value == false);
    REQUIRE(is_pointer<float[1]>::value == false);
    //float f[] = {0, 1, 2};
    //REQUIRE(is_pointer<decltype(f)>::value == true);
    REQUIRE(is_pointer<float*>::value == true);
    REQUIRE(is_pointer<int>::value == false);
}

TEST_CASE("is_lvalue_reference", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_lvalue_reference<float[]>::value == false);
    REQUIRE(is_lvalue_reference<int&>::value == true);
}

TEST_CASE("is_rvalue_reference", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_rvalue_reference<float[]>::value == false);
    REQUIRE(is_rvalue_reference<int&&>::value == true);
}

TEST_CASE("is_reference", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_reference<float[]>::value == false);
    REQUIRE(is_reference<int&>::value == true);
    REQUIRE(is_reference<int&&>::value == true);
}

TEST_CASE("is_union", "[type_traits]") {
    using namespace omega;

    //REQUIRE(is_union<float[]>::value == false);
    //REQUIRE(is_union<int&>::value == true);
    REQUIRE(is_union<int&&>::value == false);
    union U {};
    REQUIRE(is_union<U>::value == true);
}

TEST_CASE("is_class", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_class<float[]>::value == false);
    REQUIRE(is_class<int&>::value == false);
    REQUIRE(is_class<int&&>::value == false);

    class A {};
    REQUIRE(is_class<A>::value == true);
    struct S {};
    REQUIRE(is_class<S>::value == true);
    union U {};
    REQUIRE(is_class<U>::value == false);
}

// Primary classification traits:
TEST_CASE("is_enum", "[type_traits]") {
    using namespace omega;

    REQUIRE(is_enum<float[]>::value == false);
    REQUIRE(is_enum<int&>::value == false);
    REQUIRE(is_enum<int&&>::value == false);

    class A {};
    REQUIRE(is_enum<A>::value == false);
    struct S {};
    REQUIRE(is_enum<S>::value == false);
    union U {};
    REQUIRE(is_enum<U>::value == false);

    enum E {};
    REQUIRE(is_enum<E>::value == true);
    enum class EC {};
    REQUIRE(is_enum<EC>::value == true);
}


// Secondary classification traits:


// Const-volatile properties and transformations:


// Reference transformations:


// Pointer transformations:


// Integral properties:


// Array properties and transformations:


// Member introspection:


// Relationships between types:


// Alignment properties and transformations:
