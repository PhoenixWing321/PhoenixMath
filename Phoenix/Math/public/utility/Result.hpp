#ifndef PHOENIX_Result_H
#define PHOENIX_Result_H

namespace Phoenix {

struct Result {
    virtual ~Result() = default;
    int code; ///< 0: success, otherwise: ng
};

struct ValueRst : public Result {
    virtual ~ValueRst() = default;
    float value; ///< result (float format)
};

struct ValueIndexRst : public ValueRst {
    virtual ~ValueIndexRst() = default;
    double row; ///< row index (double format)
    double col; ///< col index (double format)
};

/**
 * @brief result of min and max value
 *
 */
struct LimitsRst : public Result {
    virtual ~LimitsRst() = default;
    float min; ///< min value (float format)
    float max; ///< max value (float format)
};

} // namespace Phoenix

inline std::ostream& operator<<(std::ostream& os, const Phoenix::ValueIndexRst& rst) {
    os << "{" << rst.code << "," << rst.value << "," << rst.row << "," << rst.col << "}";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Phoenix::LimitsRst& rst) {
    os << "{" << rst.code << "," << rst.min << "," << rst.max << "}";
    return os;
}
#endif