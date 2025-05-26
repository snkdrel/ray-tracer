#include <catch2/catch_test_macros.hpp>

struct Tuple {
    float x;
    float y;
    float z;
    float w;
};

bool isPoint(Tuple t) {
    if (t.w == 1.0) 
        return true;
    else 
        return false;
}

bool isVector(Tuple t) {
    if (t.w == 0.0) 
        return true;
    else 
        return false;
}

TEST_CASE ("Distinguish between points and vectors", "[tuple]") {
    
    SECTION("A tuple with w=1.0 is a point") {
        Tuple a {4.3, -4.2, 3.1, 1.0};
        REQUIRE( a.x == 4.3f );
        REQUIRE( a.y == -4.2f );
        REQUIRE( a.z == 3.1f );
        REQUIRE( a.w == 1.0f );
        REQUIRE( isPoint(a) );
        REQUIRE( !isVector(a) );
    }

    SECTION("A tuple with w=0 is a vector") {
        Tuple a {4.3, -4.2, 3.1, 0.0};
        REQUIRE( a.x == 4.3f );
        REQUIRE( a.y == -4.2f );
        REQUIRE( a.z == 3.1f );
        REQUIRE( a.w == 0.0f );
        REQUIRE( !isPoint(a) );
        REQUIRE( isVector(a) );
    }
    
}