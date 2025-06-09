#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>
#include <algorithm>
#include "tuples.h"

class Canvas {
    private:
    std::vector<std::vector<Tuple>> pixels;

    public:
    int width;
    int height;

    Canvas(int w, int h);

    Canvas(int w, int h, Tuple color);

    void write_pixel(int x, int y, Tuple color);

    Tuple pixel_at(int x, int y);

    std::string to_ppm();
};

#endif