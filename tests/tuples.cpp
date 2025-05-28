#include <catch2/catch_test_macros.hpp>
#include <cmath>

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

Tuple operator* (const Tuple& t, const float s) {
    return {t.x * s, t.y * s, t.z * s, t.w * s};
}

Tuple operator* (const float s, const Tuple& t) {
    return {t.x * s, t.y * s, t.z * s, t.w * s};
}

// check for s == 0
Tuple operator/ (const Tuple& t, const float s) {
    return {t.x / s, t.y / s, t.z / s, t.w / s};
}

Tuple point(float x, float y, float z) {
    return {x, y, z, 1.0};
}

Tuple vector(float x, float y, float z) {
    return {x, y, z, 0.0};
}

float magnitude(const Tuple& t) {
    return std::sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

// maybe modify tuple instead of returning a new one?
// check if magnitude(t) != 0?
Tuple normalize(const Tuple& t) {
    float m = magnitude(t);
    return {t.x / m, t.y / m, t.z / m, t.w / m};
}

float dot(const Tuple& a, const Tuple& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Tuple cross(const Tuple& a, const Tuple& b) {
    return vector(  a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x );
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

    SECTION ("Multiplying a tuple by a scalar") {
        Tuple a {1, -2, 3, -4};
        Tuple expected {3.5, -7, 10.5, -14};
        REQUIRE (a * 3.5 == expected);
    }

    SECTION ("Multiplying a tuple by a fraction") {
        Tuple a {1, -2, 3, -4};
        Tuple expected {0.5, -1, 1.5, -2};
        REQUIRE ((a * 0.5) == expected);
        REQUIRE ((0.5 * a) == expected);
    }

    SECTION( "Dividing a tuple by a scalar" ) {
        Tuple a {1, -2, 3, -4};
        Tuple expected {0.5, -1, 1.5, -2};
        REQUIRE((a / 2) == expected);
    }

    SECTION( "Computing the magnitude of a vector" ) {
        Tuple v1 = vector(1, 0, 0);
        REQUIRE(magnitude(v1) == 1);

        Tuple v2 = vector(0, 1, 0);
        REQUIRE(magnitude(v2) == 1);

        Tuple v3 = vector(0, 0, 1);
        REQUIRE(magnitude(v3) == 1);

        Tuple v4 = vector(1, 2, 3);
        REQUIRE(equal(magnitude(v4), std::sqrt(14)));

        Tuple v5 = vector(-1, -2, -3);
        REQUIRE(equal(magnitude(v5), std::sqrt(14)));
    }

    SECTION("Normalizing vectors") {
        Tuple v1 = vector(4, 0, 0);
        Tuple expected = vector(1, 0, 0);
        REQUIRE(normalize(v1) == expected);

        Tuple v2 = vector(1, 2, 3);
        Tuple expected2 = vector(0.26726, 0.53452, 0.80178);
        REQUIRE(normalize(v2) == expected2);

        Tuple v3 = vector(1, 2, 3);
        REQUIRE( equal(magnitude(normalize(v3)), 1) );
    }

    SECTION("The dot product of two tuples") {
        Tuple a = vector(1, 2, 3);
        Tuple b = vector(2, 3, 4);
        REQUIRE(dot(a, b) == 20);
    }

    SECTION("The cross product of two vectors") {
        Tuple a = vector(1, 2, 3);
        Tuple b = vector(2, 3, 4);
        Tuple expected = vector(-1, 2, -1);
        Tuple expected2 = vector(1, -2, 1);
        REQUIRE(cross(a, b) == expected);
        REQUIRE(cross(b, a) == expected2);
    }
}