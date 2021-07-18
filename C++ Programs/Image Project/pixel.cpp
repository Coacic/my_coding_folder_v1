#include "pixel.h"

Pixel::Pixel(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// std::ostream &operator<<(std::ostream &os, const Pixel &obj)
// {
//     os << "[" << obj.r << ", " << obj.g << ", " << obj.b << "]" << std::endl;
//     return os;
// }