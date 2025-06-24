#ifndef TUPLES_H
#define TUPLES_H

#include "tools.h"

struct Tuple {
    float x;
    float y;
    float z;
    float w;

    bool isPoint();

    bool isVector();

    Tuple operator-() const;
    
    float magnitude() const;
};

bool operator== (const Tuple& t1, const Tuple& t2);

bool operator!= (const Tuple& t1, const Tuple& t2);

// is it the user's responsibility to guarantee not to add two points?
Tuple operator+ (const Tuple& t1, const Tuple& t2);

// Should not subtract point from vector
Tuple operator- (const Tuple& t1, const Tuple& t2);

Tuple operator* (const Tuple& t, const float s);

Tuple operator* (const float s, const Tuple& t);

// check for s == 0
Tuple operator/ (const Tuple& t, const float s);

Tuple point(float x, float y, float z);

Tuple vector(float x, float y, float z);

Tuple color(float x, float y, float z);

float dot(const Tuple& a, const Tuple& b);

Tuple cross(const Tuple& a, const Tuple& b);

Tuple normalize(const Tuple& t);

Tuple hadamard_product(const Tuple& c1, const Tuple& c2);

#endif