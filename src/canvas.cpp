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
    // append header
    std::string s_out {"P3\n" + std::to_string(width) 
        + " " + std::to_string(height) + "\n255\n"};

    // append pixel data
    for (int i = 0; i < height; i++) {
        std::string row {};
        for (int j = 0; j < width; j++) {
            // interpolation 0-1 to 0-255
            int r = std::clamp(
                static_cast<int>((pixels[j][i].x * 255) + 0.5), 0, 255);
            int g = std::clamp(
                static_cast<int>((pixels[j][i].y * 255) + 0.5), 0, 255);
            int b = std::clamp(
                static_cast<int>((pixels[j][i].z * 255) + 0.5), 0, 255);

            row.append(std::to_string(r) + " ");
            // limit row to 70 characters
            limitString(row, s_out);

            row.append(std::to_string(g) + " ");
            limitString(row, s_out);

            row.append(std::to_string(b) + " ");
            limitString(row, s_out);
        }
        row[row.length() - 1] = '\n';
        s_out.append(row);
    }
    return s_out;
}

void Canvas::limitString(std::string& row, std::string& out) {
    if (row.length() > 70) {
        row[row.rfind(" ", row.length() - 2)] = '\n';
        out.append(row);
        row = "";
    }
}