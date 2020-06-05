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


// Primary classification traits:


// Secondary classification traits:


// Const-volatile properties and transformations:


// Reference transformations:


// Pointer transformations:


// Integral properties:


// Array properties and transformations:


// Member introspection:


// Relationships between types:


// Alignment properties and transformations:
