#include "tuples.h"

bool Tuple::isPoint() {
    if (w == 1) return true;
    return false;
}

bool Tuple::isVector() {
    if (w == 0) return true;
    return false;
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

Tuple color(float x, float y, float z) {
    return {x, y, z, 0.0};
}

float Tuple::magnitude() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// maybe modify tuple instead of returning a new one?
// check if magnitude(t) != 0?
Tuple normalize(const Tuple& t) {
    float m = t.magnitude();
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

Tuple hadamard_product(const Tuple& c1, const Tuple& c2) {
    return color(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z);
}