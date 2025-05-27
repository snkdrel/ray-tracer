#include <catch2/catch_test_macros.hpp>

struct Tuple {
    float x;
    float y;
    float z;
    float w;

    bool isPoint() {
        return w;
    }

    bool isVector() {
        return !isPoint();
    }

    Tuple operator-() const;
};

bool equal (float a, float b) {
    if (abs(a - b) < 0.00001) {
        return true;
    } else {
        return false;
    }
}

bool operator== (const Tuple& t1, const Tuple& t2) {
    return equal(t1.x, t2.x) && equal(t1.y, t2.y) 
        && equal(t1.z, t2.z) && equal(t1.w, t2.w);
}

bool operator!= (const Tuple& t1, const Tuple& t2) {
    return !equal(t1.x, t2.x) || !equal(t1.y, t2.y) 
        || !equal(t1.z, t2.z) || !equal(t1.w, t2.w);
}

// is it the user's responsibility to guarantee not to add two points?
Tuple operator+ (const Tuple& t1, const Tuple& t2) {
    return {t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w};
}

// Should not subtract point from vector
Tuple operator- (const Tuple& t1, const Tuple& t2) {
    return {t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w};
}

Tuple Tuple::operator- () const {
    return {-x, -y, -z, -w};
}

Tuple point(float x, float y, float z) {
    return {x, y, z, 1.0};
}

Tuple vector(float x, float y, float z) {
    return {x, y, z, 0.0};
}

TEST_CASE ("Distinguish between points and vectors", "[tuple]") {
    
    SECTION("A tuple with w=1.0 is a point") {
        Tuple a {4.3, -4.2, 3.1, 1.0};
        REQUIRE( a.x == 4.3f );
        REQUIRE( a.y == -4.2f );
        REQUIRE( a.z == 3.1f );
        REQUIRE( a.w == 1.0f );
        REQUIRE( a.isPoint() );
        REQUIRE( !a.isVector() );
    }

    SECTION("A tuple with w=0 is a vector") {
        Tuple a {4.3, -4.2, 3.1, 0.0};
        REQUIRE( a.x == 4.3f );
        REQUIRE( a.y == -4.2f );
        REQUIRE( a.z == 3.1f );
        REQUIRE( a.w == 0.0f );
        REQUIRE( !a.isPoint() );
        REQUIRE( a.isVector() );
    }

    SECTION("point() creates tuples with w=1") {
        Tuple p = point(4, -4, 3);
        REQUIRE( p.isPoint() );
        REQUIRE( p.x == 4 );
        REQUIRE( p.y == -4 );
        REQUIRE( p.z == 3 );
    }

    SECTION("vector() creates tuples with w=0") {
        Tuple p = vector(4, -4, 3);
        REQUIRE( p.isVector() );
        REQUIRE( p.x == 4 );
        REQUIRE( p.y == -4 );
        REQUIRE( p.z == 3 );
    }

    SECTION("Adding two tuples") {
        Tuple a1 {3, -2, 5, 1};
        Tuple a2 {-2, 3, 1, 0};
        Tuple expected {1, 1, 6, 1};
        REQUIRE( (a1 + a2) == expected );
    }

    SECTION("Subtracting two points") {
        Tuple p1 = point(3, 2, 1);
        Tuple p2 = point(5, 6, 7);
        Tuple expected = vector(-2, -4, -6);
        REQUIRE( (p1 - p2) == expected );
    }

    SECTION("Subtracting a vector from a point") {
        Tuple p = point(3, 2, 1);
        Tuple v = vector(5, 6, 7);
        Tuple expected = point(-2, -4, -6);
        REQUIRE ((p - v) == expected);
    }

    SECTION ("Subtracting two vectors") {
        Tuple v1 = vector(3, 2, 1);
        Tuple v2 = vector(5, 6, 7);
        Tuple expected = vector(-2, -4, -6);
        REQUIRE ((v1 - v2) == expected);
    }

    SECTION("Subtracting a vector from the zero vector") {
        Tuple zero = vector(0,0,0);
        Tuple v = vector(1,-2,3);
        Tuple expected = vector(-1, 2, -3);
        REQUIRE((zero - v) == expected);
    }

    SECTION("Negating a tuple") {
        Tuple a {1, -2, 3, -4};
        Tuple expected {-1, 2, -3, 4};
        REQUIRE (-a == expected);
    }
}