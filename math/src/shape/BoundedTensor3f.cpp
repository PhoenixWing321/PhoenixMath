#include "Phoenix/shape/BoundedTensor3f.h"

namespace Phoenix {

BoundedTensor3f::BoundedTensor3f()
    : RowTensor3f()
    , bounds() {}

BoundedTensor3f::BoundedTensor3f(const RowTensor3f& tensor, const Bounds2f& bounds)
    : RowTensor3f(tensor)
    , bounds(bounds) {}

} // namespace Phoenix