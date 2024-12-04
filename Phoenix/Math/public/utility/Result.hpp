#ifndef PHOENIX_Result_H
#define PHOENIX_Result_H

namespace Phoenix {

/**
 * @brief result of value
 */
struct Result {
    Result()
        : code(0) {}

    virtual ~Result() = default;
    int code; ///< 0: success, otherwise: ng
};

/**
 * @brief result of value
 */
struct ValueRst : public Result {
    ValueRst()
        : Result()
        , value(std::numeric_limits<float>::lowest()) {}

    virtual ~ValueRst() = default;

    float value; ///< result (float format)
};

/**
 * @brief result of value and its position
 */
struct ValueIndexRst : public ValueRst {
    ValueIndexRst()
        : ValueRst()
        , row(-1)
        , col(-1) {}

    virtual ~ValueIndexRst() = default;

    double row; ///< row index (double format)
    double col; ///< col index (double format)
};

/**
 * @brief result of min and max value
 *
 */
struct LimitsRst : public Result {
    LimitsRst()
        : Result()
        , min(std::numeric_limits<float>::max())
        , max(std::numeric_limits<float>::lowest()) {}

    virtual ~LimitsRst() = default;

    float min; ///< min value (float format)
    float max; ///< max value (float format)
};

/**
 * @brief result of min, max value and their position
 */
struct LimitsBoundsPosRst : public LimitsRst {
    LimitsBoundsPosRst()
        : LimitsRst()
        , pos_min(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest())
        , pos_max(pos_min) {}

    virtual ~LimitsBoundsPosRst() = default;

    glm::vec2 pos_min; ///< position of min value
    glm::vec2 pos_max; ///< position of max value
};

} // namespace Phoenix

/**
 * @brief print result of code, value and (min index, max index)
 */
inline std::ostream& operator<<(std::ostream& os, const Phoenix::ValueIndexRst& rst) {
    os << "{" << rst.code << ", " << rst.value << ", (" << rst.row << ", " << rst.col << ")}";
    return os;
}

/**
 * @brief print result of code, min, max value and their position
 */
inline std::ostream& operator<<(std::ostream& os, const Phoenix::LimitsBoundsPosRst& rst) {
    os << "{" << rst.code << ", [" << rst.min << " ~ " << rst.max << "], (" << rst.pos_min.x << ", "
       << rst.pos_min.y << "), (" << rst.pos_max.x << ", " << rst.pos_max.y << ")}";
    return os;
}

/**
 * @brief print result of code, min, max value
 */
inline std::ostream& operator<<(std::ostream& os, const Phoenix::LimitsRst& rst) {
    os << "{" << rst.code << ", [" << rst.min << " ~ " << rst.max << "]}";
    return os;
}
#endif