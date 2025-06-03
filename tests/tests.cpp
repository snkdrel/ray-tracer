#include <catch2/catch_test_macros.hpp>
#include "../src/tuples.h"
#include "../src/canvas.h"

TEST_CASE("Canvas creation", "[canvas]") {
    Canvas c = Canvas(10, 20);
    REQUIRE(c.width == 10);
    REQUIRE(c.height == 20);
    
    Tuple black = color(0, 0, 0);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            CHECK(c.pixel_at(i, j) == black);
        }
    }

    SECTION("Writing pixels to a canvas") {
        Tuple red = color(1, 0, 0);
        c.write_pixel(2, 3, red);
        REQUIRE(c.pixel_at(2, 3) == red);
    }
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
        REQUIRE(v1.magnitude() == 1);

        Tuple v2 = vector(0, 1, 0);
        REQUIRE(v2.magnitude() == 1);

        Tuple v3 = vector(0, 0, 1);
        REQUIRE(v3.magnitude() == 1);

        Tuple v4 = vector(1, 2, 3);
        REQUIRE(equal(v4.magnitude(), std::sqrt(14)));

        Tuple v5 = vector(-1, -2, -3);
        REQUIRE(equal(v5.magnitude(), std::sqrt(14)));
    }

    SECTION("Normalizing vectors") {
        Tuple v1 = vector(4, 0, 0);
        Tuple expected = vector(1, 0, 0);
        REQUIRE(normalize(v1) == expected);

        Tuple v2 = vector(1, 2, 3);
        Tuple expected2 = vector(0.26726, 0.53452, 0.80178);
        REQUIRE(normalize(v2) == expected2);

        Tuple v3 = vector(1, 2, 3);
        REQUIRE( equal(normalize(v3).magnitude(), 1) );
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

    SECTION("Colors are (red, green, blue) tuples") {
        Tuple c = color(-0.5, 0.4, 1.7);
        REQUIRE(equal(c.x, -0.5));
        REQUIRE(equal(c.y, 0.4));
        REQUIRE(equal(c.z, 1.7));
    }

    SECTION("Operations between colors") {
        Tuple c1 = color(0.9, 0.6, 0.75);
        Tuple c2 = color(0.7, 0.1, 0.25);
        Tuple expected = color(1.6, 0.7, 1.0);
        REQUIRE(c1 + c2 == expected);

        Tuple expected2 = color(0.2, 0.5, 0.5);
        REQUIRE(c1 - c2 == expected2);

        Tuple c3 = color(0.2, 0.3, 0.4);
        Tuple expected3 = color(0.4, 0.6, 0.8);
        REQUIRE(c3 * 2 == expected3);

        Tuple c4 = color(1, 0.2, 0.4);
        Tuple c5 = color(0.9, 1, 0.1);
        Tuple expected4 = color(0.9, 0.2, 0.04);
        REQUIRE(hadamard_product(c4, c5) == expected4);
    }
}