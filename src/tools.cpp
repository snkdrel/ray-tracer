#include "tools.h"

bool equal (float a, float b) {
    if (abs(a - b) < 0.00001) {
        return true;
    } else {
        return false;
    }
}