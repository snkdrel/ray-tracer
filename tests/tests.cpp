#include <catch2/catch_test_macros.hpp>
#include "../src/tools.h"
#include "../src/tuples.h"
#include "../src/canvas.h"
#include "../src/matrices.h"
#include "../src/transformations.h"
#include <iostream>

TEST_CASE("Matrix transformations", "[transformations]") {
    SECTION("Translation") {
        // Multiplying by a translation matrix
        Matrix transform = translation(5, -3, 2);
        Tuple p = point(-3, 4, 5);
        REQUIRE(transform * p == point(2, 1, 7));

        // Multiplying by the inverse of a translation matrix
        Matrix inv = inverse(transform);
        REQUIRE(inv * p == point(-8, 7, 3));

        // Translation does not affect vectors
        Tuple v = vector(-3, 4, 5);
        REQUIRE(transform * v == v);
    }

    SECTION("Scaling") {
        // A scaling matrix applied to a point
        Matrix transform = scaling(2, 3, 4);
        Tuple p = point(-4, 6, 8);
        REQUIRE(transform * p == point(-8, 18, 32));

        // A scaling matrix applied to a vector
        Tuple v = vector(-4, 6, 8);
        REQUIRE(transform * v == vector(-8, 18, 32));

        // Multiplying by the inverse of a scaling matrix
        Matrix inv = inverse(transform);
        REQUIRE(inv * v == vector(-2, 2, 2));

        // Reflection is scaling by a negative value
        Matrix reflection = scaling(-1, 1, 1);
        Tuple p2 = point(2, 3, 4);
        REQUIRE(reflection * p2 == point(-2, 3, 4));
    }

    SECTION("Rotating a point around the x axis") {
        Tuple p = point(0, 1, 0);
        Matrix half_quarter = rotation_x(M_PI / 4);
        Matrix full_quarter = rotation_x(M_PI / 2);
        REQUIRE(half_quarter * p == 
                    point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
        REQUIRE(full_quarter * p == point(0, 0, 1));

        // The inverse of an x-rotation rotates in the opposite direction
        Matrix inv = inverse(half_quarter);
        REQUIRE(inv * p == point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
    }

    SECTION("Rotating a point around the y axis") {
        Tuple p = point(0, 0, 1);
        Matrix half_quarter = rotation_y(M_PI / 4);
        Matrix full_quarter = rotation_y(M_PI / 2);
        REQUIRE(half_quarter * p == 
                point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
        REQUIRE(full_quarter * p == point(1, 0, 0));
    }

    SECTION("Rotating a point around the z axis") {
        Tuple p = point(0, 1, 0);
        Matrix half_quarter = rotation_z(M_PI / 4);
        Matrix full_quarter = rotation_z(M_PI / 2);
        REQUIRE(half_quarter * p == 
                point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
        REQUIRE(full_quarter * p == point(-1, 0, 0));
    }
}

TEST_CASE("Matrices operations", "[matrices]") {
    SECTION("Constructing and inspecting matrices") {
        Matrix m = {{1,2,3,4},
                    {5.5, 6.5, 7.5, 8.5},
                    {9, 10, 11, 12},
                    {13.5, 14.5, 15.5, 16.5}};
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][3] == 4);
        REQUIRE(m[1][0] == 5.5);
        REQUIRE(m[1][2] == 7.5);
        REQUIRE(m[2][2] == 11);
        REQUIRE(m[3][0] == 13.5);
        REQUIRE(m[3][2] == 15.5);

        Matrix m2 = {{-3, 5},
                    {1, -2}};
        REQUIRE(m2[0][0] == -3);
        REQUIRE(m2[0][1] == 5);
        REQUIRE(m2[1][0] == 1);
        REQUIRE(m2[1][1] == -2);

        Matrix m3 = { {-3, 5, 0},
                      {1, -2, -7},
                      {0, 1, 1}};
        REQUIRE(m3[0][0] == -3);
        REQUIRE(m3[1][1] == -2);
        REQUIRE(m3[2][2] == 1);
    }
    
    SECTION("Matrix equality with identical matrices") {
        Matrix a = { {1 , 2 , 3 , 4 },
                    { 5 , 6 , 7 , 8 },
                    { 9 , 8 , 7 , 6 },
                    { 5 , 4 , 3 , 2 } };
        Matrix b = { {1 , 2 , 3 , 4 },
                    { 5 , 6 , 7 , 8 },
                    { 9 , 8 , 7 , 6 },
                    { 5 , 4 , 3 , 2 } };
        REQUIRE (a == b);

        Matrix c = { {2 , 3,  4 , 5},
                    {6 , 7 , 8 , 9},
                    {8 , 7 , 6 , 5},
                    {4 , 3 , 2 , 1} };
        REQUIRE(a != c);
    }

    SECTION("Multiplying two matrices") {
        Matrix a = { { 1 , 2 , 3 , 4 },
                { 5 , 6 , 7 , 8 },
                { 9 , 8 , 7 , 6 },
                { 5 , 4 , 3 , 2 } };
        Matrix b = { { -2 , 1 , 2 , 3 },
                    { 3 , 2 , 1 , -1 },
                    { 4 , 3 , 6 , 5 },
                    { 1 , 2 , 7 , 8 }};
        Matrix res = { {20, 22 , 50 , 48 },
                    { 44, 54 , 114 , 108 },
                    { 40, 58 , 110 , 102 },
                    { 16, 26 , 46 , 42 } };
        REQUIRE (res == (a * b));
    }

    SECTION("A matrix multiplied by a tuple") {
        Matrix a = { { 1 , 2 , 3 , 4 },
                     { 2 , 4 , 4 , 2 },
                     { 8 , 6 , 4 , 1 },
                     { 0 , 0 , 0 , 1 } };
        Tuple b = {1, 2, 3, 1};
        Tuple res = {18, 24, 33, 1};
        REQUIRE( a * b == res);
    }

    SECTION("Multiplying a matrix by the identity matrix") {
        Matrix a = {{ 0 , 1 , 2 , 4 },
                    { 1 , 2 , 4 , 8 },
                    { 2 , 4 , 8 , 16 },
                    { 4 , 8 , 16 , 32} };
        REQUIRE( a * matrices::identity == a );
        
        Tuple t {1, 2, 3, 4};
        REQUIRE( matrices::identity * t == t );
    }

    SECTION("Transposing a matrix") {
        Matrix a =  {{ 0 , 9 , 3 , 0 },
                    { 9 , 8 , 0 , 8 },
                    { 1 , 8 , 5 , 3 },
                    { 0 , 0 , 5 , 8} };

        Matrix at =  {{ 0 , 9 , 1 , 0 },
                    { 9 , 8 , 8 , 0 },
                    { 3 , 0 , 5 , 5 },
                    { 0 , 8 , 3 , 8} };
        
        REQUIRE( transpose(a) == at );

        REQUIRE( matrices::identity == transpose(matrices::identity) );
    }
}

TEST_CASE("Inverting matrices", "[matrices]") {
    SECTION("Calculating the determinant of a 2x2 matrix") {
        Matrix A = {{1, 5}, {-3, 2}};
        REQUIRE(determinant(A) == 17);
    }

    SECTION("Extracting submatrices from matrices") {
        Matrix A = {{1 , 5 , 0 },
                    { -3 , 2 , 7 },
                    { 0 , 6 , -3}};
        Matrix subA = {{-3, 2}, {0, 6}};
        REQUIRE( submatrix(A, 0, 2) == subA);

        Matrix B =  {{ -6 , 1 , 1 , 6 },
                    { -8 , 5 , 8 , 6 },
                    { -1 , 0 , 8 , 2 },
                    { -7 , 1 , -1 , 1} };
        Matrix subB = {{ -6 , 1 , 6 },
                       { -8 , 8 , 6 },
                       { -7 , -1 , 1} };
        REQUIRE(submatrix(B, 2, 1) == subB);
    }

    SECTION("Calculating a minor of a 3x3 matrix") {
        Matrix A = {{ 3 , 5 , 0 },
                    { 2 , -1 , -7 },
                    { 6 , -1 , 5} };
        Matrix B = submatrix(A, 1, 0);
        REQUIRE(determinant(B) == 25);
        REQUIRE( minor(A, 1, 0) == 25 );
    }

    SECTION("Calculating a cofactor of a 3x3 matrix") {
        Matrix A = {{ 3 , 5 , 0 },
                    { 2 , -1 , -7 },
                    { 6 , -1 , 5} };
        REQUIRE( minor(A, 0, 0) == -12);
        REQUIRE( cofactor(A, 0, 0) == -12);
        REQUIRE( minor(A, 1, 0) == 25 );
        REQUIRE( cofactor(A, 1, 0) == -25);
    }

    SECTION("Calculating the determinant of a 3x3 matrix") {
        Matrix A = {{ 1 , 2 , 6 },
                    { -5 , 8 , -4 },
                    { 2 , 6 , 4} };
        REQUIRE( cofactor(A, 0, 0) == 56 );
        REQUIRE( cofactor(A, 0, 1) == 12 );
        REQUIRE( cofactor(A, 0, 2) == -46 );
        REQUIRE( determinant(A) == -196 );
    }

    SECTION("Calculating the determinant of a 4x4 matrix") {
        Matrix A =  {{ -2 , -8 , 3 , 5 },
                     { -3 , 1 , 7 , 3 },
                     { 1 , 2 , -9 , 6 },
                     { -6 , 7 , 7 , -9 } };
        REQUIRE( cofactor(A, 0, 0) == 690 );
        REQUIRE( cofactor(A, 0, 1) == 447 );
        REQUIRE( cofactor(A, 0, 2) == 210 );
        REQUIRE( cofactor(A, 0, 3) == 51 );
        REQUIRE( determinant(A) == -4071 );
    }

    SECTION("Testing an invertible matrix for invertibility") {
        Matrix A =  {{ 6 , 4 , 4 , 4 },
                     { 5 , 5 , 7 , 6 },
                     { 4 , -9 , 3 , -7 },
                     { 9 , 1 , 7 , -6 } };
        REQUIRE( determinant(A) == -2120 );
        REQUIRE( isInvertible(A) );

        Matrix B =  {{ -4 , 2 , -2 , -3 },
                     { 9 , 6 ,2 , 6 },
                     { 0 , -5 , 1 , -5 },
                     { 0 , 0 , 0 , -0 } };
        REQUIRE( determinant(B) == 0 );
        REQUIRE( !isInvertible(B) );
    }

    SECTION("Calculating the inverse of a matrix") {
        Matrix A =  {{ -5 , 2 , 6 , -8 },
                     { 1 , -5 , 1 , 8 },
                     { 7 , 7 , -6 , -7 },
                     { 1 , -3 , 7 , 4 } };
        Matrix B = inverse(A);
        Matrix res = {{ 0.21805 , 0.45113 , 0.24060 , -0.04511 },
                      { -0.80827 , -1.45677 , -0.44361 , 0.52068 },
                      { -0.07895 , -0.22368 , -0.05263 , 0.19737 },
                      { -0.52256 , -0.81391 , -0.30075 , 0.30639 } };
        CHECK( determinant(A) == 532 );
        CHECK( cofactor(A, 2, 3) == -160 );
        CHECK( equal(B[3][2], -160/532 ) );
        CHECK( cofactor(A, 3, 2) == 105 );
        CHECK( equal(B[2][3], 105/532 ) );
        REQUIRE( res == B );

        Matrix C =  {{ 8 , -5 , 9 , 2 },
                     { 7 , 5 , 6 , 1 },
                     { -6 , 0 , 9 , 6 },
                     { -3 , 0 , -9 , -4 } };
        Matrix invC = {{ -0.15385 , -0.15385 , -0.28205 , -0.53846 },
                    { -0.07692 , 0.12308 , 0.02564 , 0.03077 },
                    { 0.35897 , 0.35897 , 0.43590 , 0.92308 },
                    { -0.69231 , -0.69231 , -0.76923 , -1.92308 }};
        REQUIRE(invC == inverse(C));

        Matrix D =  {{ 9 , 3 , 0 , 9 },
                     { -5 , -2 , -6 , -3 },
                     { -4 , 9 , 6 , 4 },
                     { -7 , 6 , 6 , 2 } };
        Matrix invD = {{-0.04074 , -0.07778 , 0.14444 , -0.22222 },
                    { -0.07778 , 0.03333 , 0.36667 , -0.33333 },
                    { -0.02901 , -0.14630 , -0.10926 , 0.12963 },
                    { 0.17778 , 0.06667 , -0.26667 , 0.33333} };
        REQUIRE (invD == inverse(D));
    }

    SECTION("Multiplying a product by its inverse") {
        Matrix A =  {{ 3 , -9 , 7 , 3 },
                     { 3 , -8 , 2 , -9 },
                     { -4 , 4 , 4 , 1 },
                     { -6 , 5 , -1 , 1 } };
        Matrix B =  {{ 8 , 2 , 2 , 2 },
                    { 3 , -1 , 7 , 0 },
                    { 7 , 0 , 5 , 4 },
                    { 6 , -2 , 0 , 5 } };
        Matrix C = A * B;
        REQUIRE (C * inverse(B) == A);

        Matrix invI = inverse(matrices::identity);
        REQUIRE (invI == matrices::identity);
        
        REQUIRE (A * inverse(A) == matrices::identity);
        
        REQUIRE (inverse(transpose(A)) == transpose(inverse(A)));
    }
}

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

TEST_CASE("Constructing PPM data", "[canvas]") {
    Canvas c = Canvas(5, 3);

    SECTION("Constructing the PPM header") {
        std::string ppm = c.to_ppm();
        REQUIRE(ppm.rfind("P3\n5 3\n255\n", 0) == 0);
    }

    SECTION("Constructing the PPM pixel data") {
        Tuple c1 = color(1.5, 0, 0);
        Tuple c2 = color(0, 0.5, 0);
        Tuple c3 = color(-0.5, 0, 1);

        c.write_pixel(0, 0, c1);
        c.write_pixel(2, 1, c2);
        c.write_pixel(4, 2, c3);

        std::string ppm = c.to_ppm();
        std::string s = "P3\n5 3\n255\n"
                        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
        REQUIRE(ppm == s);
    }

    SECTION("Splitting long lines in PPM files") {
        Tuple c1 = color(1, 0.8, 0.6);
        Canvas canvas = Canvas(10, 2, c1);
        std::string ppm = canvas.to_ppm();
        std::string s = "P3\n10 2\n255\n"
                        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
        REQUIRE(ppm == s);
    }

    SECTION("PPM files are terminated by a newline character") {
        Canvas canvas = Canvas(5, 3);
        std::string ppm = canvas.to_ppm();
        REQUIRE(ppm.find("\n", ppm.length()-1));
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