#include "matrices.h"

bool operator==(const Matrix& m1, const Matrix& m2) {
    for (int i = 0; i < m1.size(); i++) {
        for (int j = 0; j < m1[0].size(); j++) {
            if (!equal(m1[i][j], m2[i][j])) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2)  {
    for (int i = 0; i < m1.size(); i++) {
        for (int j = 0; j < m1[0].size(); j++) {
            if (!equal(m1[i][j], m2[i][j])) {
                return true;
            }
        }
    }
    return false;
}