#ifndef Phoenix_Bounds2f_H
#define Phoenix_Bounds2f_H

#include <Eigen/Dense>
#include <iostream>

namespace Phoenix {
class Bounds2f {
public:
    Bounds2f()
        : b_min(Eigen::Vector2f::Zero())
        , b_max(Eigen::Vector2f::Zero()) {}
    Bounds2f(const Eigen::Vector2f& min, const Eigen::Vector2f& max)
        : b_min(min)
        , b_max(max) {}

    // Check if a point is inside the bounding box
    bool contains(const Eigen::Vector2f& point) const {
        return (point.x() >= b_min.x() && point.x() <= b_max.x() && point.y() >= b_min.y() &&
                point.y() <= b_max.y());
    }

    // Get the center of the bounding box
    Eigen::Vector2f center() const {
        return (b_min + b_max) / 2.0f;
    }

    // Expand the bounding box to include a point
    void expand(const Eigen::Vector2f& point) {
        b_min = b_min.cwiseMin(point);
        b_max = b_max.cwiseMax(point);
    }

    // Merge another bounding box into this one
    void expand(const Bounds2f& other) {
        b_min = b_min.cwiseMin(other.b_min);
        b_max = b_max.cwiseMax(other.b_max);
    }

public:
    Eigen::Vector2f b_min;
    Eigen::Vector2f b_max;
};
} // namespace Phoenix

#endif