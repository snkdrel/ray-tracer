#include "canvas.h"

Canvas::Canvas(int w, int h) : width {w}, height {h} 
{
    pixels = std::vector<std::vector<Tuple>> (w, 
        std::vector<Tuple>(h, color(0, 0, 0)));
}

Canvas::Canvas(int w, int h, Tuple color)
: width {w}, height {h}
{
    pixels = std::vector<std::vector<Tuple>> (w, 
        std::vector<Tuple>(h, color));
}

void Canvas::write_pixel(int x, int y, Tuple color) {
    pixels[x][y] = color;
}

Tuple Canvas::pixel_at(int x, int y) {
    return pixels[x][y];
}

std::string Canvas::to_ppm() {
    std::string s_out {"P3\n" + std::to_string(width) 
        + " " + std::to_string(height) + "\n255\n"};

    // append pixel data
    for (int i = 0; i < pixels.size(); i++) {
        std::string row {};
        for (int j = 0; j < pixels[0].size(); j++) {
            int r = std::clamp(
                static_cast<int>(pixels[i][j].x * 255), 0, 255);
            int g = std::clamp(
                static_cast<int>(pixels[i][j].y * 255), 0, 255);
            int b = std::clamp(
                static_cast<int>(pixels[i][j].z * 255), 0, 255);

            row.append(std::to_string(r) + " ");
            if (row.length() > 70) {
                row[row.rfind(" ", row.length() - 2)] = '\n';
            }

            row.append(std::to_string(g) + " ");
            if (row.length() > 70) {
                row[row.rfind(" ", row.length() - 2)] = '\n';
            }

            row.append(std::to_string(b) + " ");
            if (row.length() > 70) {
                row[row.rfind(" ", row.length() - 2)] = '\n';
            }
        }
        row[row.length() - 1] = '\n';
        s_out.append(row);
    }
    return s_out;
}