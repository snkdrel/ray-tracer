#include "canvas.h"

Canvas::Canvas(int w, int h) : width {w}, height {h} 
{
    pixels = std::vector<std::vector<Tuple>> (w, 
        std::vector<Tuple>(h, color(0, 0, 0)));
}

void Canvas::write_pixel(int x, int y, Tuple color) {
    pixels[x][y] = color;
}

Tuple Canvas::pixel_at(int x, int y) {
    return pixels[x][y];
}