#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrices.h"

Matrix translation(float x, float y, float z);

Matrix scaling(float x, float y, float z);

Matrix rotation_x(float r);

Matrix rotation_y(float r);

Matrix rotation_z(float r);

#endif