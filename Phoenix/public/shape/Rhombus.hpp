#ifndef PHOENIX_Rhombus_H
#define PHOENIX_Rhombus_H

#include <iostream>

namespace Phoenix {
class Rhombus {
public:
    // Default constructor
    Rhombus()
        : a(1)
        , b(1) {}

    // Constructor a and b
    Rhombus(float a, float b)
        : a(a)
        , b(b) {}

public:
    bool operator==(const Rhombus& other) const {
        return a == other.a && b == other.b;
    }

public:
    float a; ///< long side of the rhombus (x-coordinate)
    float b; ///< short side of the rhombus (y-coordinate)
};
} // namespace Phoenix

inline std::ostream& operator<<(std::ostream& os, const Phoenix::Rhombus& rhombus) {
    os << "{" << rhombus.a << ", " << rhombus.b << "}";
    return os;
}
#endif