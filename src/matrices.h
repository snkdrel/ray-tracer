#ifndef MATRICES_H
#define MATRICES_H

#include "tools.h"
#include "vector"
#include "tuples.h"

using Matrix = std::vector<std::vector<float>>;

bool operator==(const Matrix& m1, const Matrix& m2);

bool operator!=(const Matrix& m1, const Matrix& m2);

Matrix operator*(const Matrix& m1, const Matrix& m2);

Tuple operator*(const Matrix& m, const Tuple& t);

// maybe overload vector times matrix
// it can be implemented as
// transpose(x)*A = transpose(transpose(A) * x)

#endif