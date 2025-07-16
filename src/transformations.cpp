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

Matrix rotation_x(float r) {
    Matrix res = matrices::identity;

    res[1][1] = std::cos(r);
    res[1][2] = -std::sin(r);
    res[2][1] = std::sin(r);
    res[2][2] = std::cos(r);

    return res;
}

Matrix rotation_y(float r) {
    Matrix res = matrices::identity;

    res[0][0] = std::cos(r);
    res[0][2] = std::sin(r);
    res[2][0] = -std::sin(r);
    res[2][2] = std::cos(r);

    return res;
}

Matrix rotation_z(float r) {
    Matrix res = matrices::identity;

    res[0][0] = std::cos(r);
    res[0][1] = -std::sin(r);
    res[1][0] = std::sin(r);
    res[1][1] = std::cos(r);

    return res;
}

Matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) {
    Matrix res = matrices::identity;

    res[0][1] = x_y;
    res[0][2] = x_z;
    res[1][0] = y_x;
    res[1][2] = y_z;
    res[2][0] = z_x;
    res[2][1] = z_y;

    return res;
}