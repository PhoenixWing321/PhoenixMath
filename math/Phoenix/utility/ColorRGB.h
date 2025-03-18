#ifndef PHOENIX_ColorRGB_H
#define PHOENIX_ColorRGB_H

namespace Phoenix {

struct ColorRGB {
    unsigned char r, g, b;

    enum ColorFormat {
        GRAY_SCALE = 0,
        HEAT_MAP   = 1,
        LUMINANCE  = 2,
    };

    /**
     * @brief change color to ratio    [0,1]
     * @param color RGB color
     * @param format convert format
     * @return ratio [0,1]
     */
    static float color_to_ratio(const ColorRGB& color, int format);

    /**
     * @brief change ratio to color
     * @param ratio [0,1]
     * @param format convert format
     * @return RGB color
     */
    static ColorRGB ratio_to_color(float ratio, int format); // = HEAT_MAP
};
} // namespace Phoenix
#endif // PHOENIX_ColorRGB_H
