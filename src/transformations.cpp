#include "transformations.h"

Matrix translation(float x, float y, float z) {
    Matrix res = matrices::identity;

    res[0][3] = x;
    res[1][3] = y;
    res[2][3] = z;

    return res;
}

Matrix scaling(float x, float y, float z) {
    Matrix res = matrices::identity;

    res[0][0] = x;
    res[1][1] = y;
    res[2][2] = z;

    return res;
}