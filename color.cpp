#include "color.h"

void write_color(std::ostream& out, const Color &pixel_color, const int samples_per_pixel) {
    const auto scale = 1.0 / samples_per_pixel;

    // Divide color by number of samples and gamma correct for gamma=2.0
    const auto r = sqrt(pixel_color.x() * scale);
    const auto g = sqrt(pixel_color.y() * scale);
    const auto b = sqrt(pixel_color.z() * scale);

    // Write color value for this pixel
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
