#ifndef MATRICES_H
#define MATRICES_H

#include "tools.h"
#include "vector"

using Matrix = std::vector<std::vector<float>>;

bool operator==(const Matrix& m1, const Matrix& m2);

bool operator!=(const Matrix& m1, const Matrix& m2);

#endif