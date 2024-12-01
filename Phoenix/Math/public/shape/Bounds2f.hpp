#ifndef PHOENIX_Bounds2f_H
#define PHOENIX_Bounds2f_H

#include "glm/glm.hpp"
#include <Eigen/Dense>
#include <iostream>

namespace Phoenix {
class Bounds2f {
public:
    // Default constructor
    Bounds2f()
        : b_min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max())
        , b_max(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()) {}

    // Constructor with min and max points
    Bounds2f(const glm::vec2& min, const glm::vec2& max)
        : b_min(min)
        , b_max(max) {}

    // Constructor with left, bottom, right, and top values
    Bounds2f(float left, float bottom, float right, float top)
        : b_min(left, bottom)
        , b_max(right, top) {}

public:
    bool operator==(const Bounds2f& other) const {
        return b_min == other.b_min && b_max == other.b_max;
    }

public:
    // Check if a point is inside the bounding box
    bool contains(const glm::vec2& point) const {
        return (point.x >= b_min.x && point.x <= b_max.x && point.y >= b_min.y &&
                point.y <= b_max.y);
    }

    // Get the center of the bounding box
    glm::vec2 center() const {
        return (b_min + b_max) / 2.0f;
    }

    // Expand the bounding box to include a point
    void expand(const glm::vec2& pos) {
        b_min = glm::min(pos, b_min);
        b_max = glm::max(pos, b_max);
    }

    // Merge another bounding box into this one
    void expand(const Bounds2f& other) {
        b_min = glm::min(other.b_min, b_min);
        b_max = glm::max(other.b_max, b_max);
    }

public:
    union
    {
        struct {
            glm::vec2 b_min;
            glm::vec2 b_max;
        };
        struct {
            float left;   ///< Left boundary of the rectangular area (x-coordinate)
            float bottom; ///< Bottom boundary of the rectangular area (y-coordinate)
            float right;  ///< Right boundary of the rectangular area (x-coordinate)
            float top;    ///< Top boundary of the rectangular area (y-coordinate)
        };
    };
};
} // namespace Phoenix

#endif