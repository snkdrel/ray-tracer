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

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    // check if matrices are 4x4?
    Matrix res = {{0, 0, 0, 0},
                 {0, 0, 0, 0},
                 {0, 0, 0, 0},
                 {0, 0, 0, 0}};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = m1[i][0] * m2[0][j] +
                        m1[i][1] * m2[1][j] +
                        m1[i][2] * m2[2][j] +
                        m1[i][3] * m2[3][j];
        }
    }

    return res;
}

Tuple operator*(const Matrix& m, const Tuple& t) {
    Tuple res;
    
    res.x = m[0][0] * t.x +
            m[0][1] * t.y +
            m[0][2] * t.z +
            m[0][3] * t.w;

    res.y = m[1][0] * t.x +
            m[1][1] * t.y +
            m[1][2] * t.z +
            m[1][3] * t.w;
    
    res.z = m[2][0] * t.x +
            m[2][1] * t.y +
            m[2][2] * t.z +
            m[2][3] * t.w;
        
    res.w = m[3][0] * t.x +
            m[3][1] * t.y +
            m[3][2] * t.z +
            m[3][3] * t.w;
    
    return res;
}

Matrix transpose(const Matrix& m) {
    Matrix res = m;

    for (int i = 0; i < res.size(); i++) {
        for (int j = i; j < res[0].size(); j++) {
            std::swap( res[i][j], res[j][i] );
        }
    }
    return res;
}

float determinant(const Matrix& m) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

Matrix submatrix(const Matrix& m, int row, int col) {
    int n = m.size();
    Matrix subm (n - 1, std::vector<float>(n - 1));

    int isub = 0, jsub = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        jsub = 0;
        for (int j = 0; j < n; j++) {
            if (j == col) continue;
            subm[isub][jsub] = m[i][j];
            jsub++;
        }
        isub++;
    }

    return subm;
}

float minor(const Matrix& m, int row, int col) {
    return determinant(submatrix(m, row, col));
}

float cofactor(const Matrix& m, int row, int col) {
    if ( (row + col) % 2 == 0 ) {
        return minor(m, row, col);
    } else {
        return minor(m, row, col) * -1;
    }
}