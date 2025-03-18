#ifndef PHOENIX_StreamTools_H
#define PHOENIX_StreamTools_H

#include <iostream>
#include <sstream> // for stringstream

namespace Phoenix {

/**
 * @brief result of value
 */
struct StreamTools {

    /**
     * @brief Write delimiter: tab or newline
     * @param stream stringstream object
     * @param current current position
     * @param last last position
     * @param break_count break count
     */
    static void write_delimiter(std::stringstream& stream, size_t current, size_t last,
                                int break_count) {
        if ((current + 1) % break_count == 0 || current == last)
            stream << "\n";
        else
            stream << "\t";
    }
};
} // namespace Phoenix

#endif