#ifndef INSIDE_HPP
#define INSIDE_HPP

#include <Eigen/Dense>
#include <vector>

namespace Math {
bool inside(const Eigen::Vector2d& point, const std::vector<Eigen::Vector2d>& polygon) {
    int n = polygon.size();
    if (n < 3) return false; // A polygon must have at least 3 vertices

    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Eigen::Vector2d& vi = polygon[ i ];
        const Eigen::Vector2d& vj = polygon[ j ];

        if (((vi.y() > point.y()) != (vj.y() > point.y())) &&
            (point.x() < (vj.x() - vi.x()) * (point.y() - vi.y()) / (vj.y() - vi.y()) + vi.x())) {
            inside = !inside;
        }
    }
    return inside;
}
} // namespace Math

#endif // INSIDE_HPP
