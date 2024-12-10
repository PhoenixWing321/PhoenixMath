#include "utility/ColorRGB.h"

#include <algorithm>

namespace Phoenix {
//----------------------------------
ColorRGB ColorRGB::ratio_to_color(float ratio, int format) {

    // Ensure ratio is in [0,1]
    ratio = std::clamp(ratio, 0.0f, 1.0f);
    ColorRGB color;

    switch (format) {
    case HEAT_MAP: {

        // Blue to Cyan to Green to Yellow to Red
        if (ratio < 0.25f) {
            // Blue to Cyan (0.0 - 0.25)
            float t = ratio * 4;
            color.r = 0;
            color.g = static_cast<unsigned char>(255 * t);
            color.b = 255;
        }
        else if (ratio < 0.5f) {
            // Cyan to Green (0.25 - 0.5)
            float t = (ratio - 0.25f) * 4;
            color.r = 0;
            color.g = 255;
            color.b = static_cast<unsigned char>(255 * (1 - t));
        }
        else if (ratio < 0.75f) {
            // Green to Yellow (0.5 - 0.75)
            float t = (ratio - 0.5f) * 4;
            color.r = static_cast<unsigned char>(255 * t);
            color.g = 255;
            color.b = 0;
        }
        else {
            // Yellow to Red (0.75 - 1.0)
            float t = (ratio - 0.75f) * 4;
            color.r = 255;
            color.g = static_cast<unsigned char>(255 * (1 - t));
            color.b = 0;
        }
    } break;
    case LUMINANCE: {
        // Y = 0.299R + 0.587G + 0.114B
        color.r = static_cast<unsigned char>(ratio * 255);
        color.g = color.r;
        color.b = color.r;
    } break;
    default: { // GRAY_SCALE
        // Convert ratio to grayscale value
        auto gray = static_cast<unsigned char>(ratio * 255);
        color.r   = gray;
        color.g   = gray;
        color.b   = gray;
    } break;
    }

    return color;
}
//----------------------------------
float ColorRGB::color_to_ratio(const ColorRGB& color, int format) {
    static constexpr float ratio255 = 1.0f / 255.0f;

    switch (format) {
    case HEAT_MAP: {
        // change color to value    [0,1]
        if (color.r == 0) {
            if (color.b == 255) {
                // Blue to Cyan (0.0 - 0.25)
                return (color.g * ratio255) * 0.25f;
            }
            else if (color.g == 255) {
                // Cyan to Green (0.25 - 0.5)
                return 0.25f + (1.0f - color.b * ratio255) * 0.25f;
            }
            else {
                // r=0 但 b,g 都不是255，找出较大的那个作为主导色
                if (color.b >= color.g) {
                    // 偏蓝色，映射到 Blue to Cyan 区间
                    return (color.g * ratio255) * 0.25f;
                }
                else {
                    // 偏绿色，映射到 Cyan to Green 区间
                    return 0.25f + (1.0f - color.b * ratio255) * 0.25f;
                }
            }
        }
        else if (color.g == 255 && color.b == 0) {
            // Green to Yellow (0.5 - 0.75)
            return 0.5f + (color.r * ratio255) * 0.25f;
        }
        else if (color.r == 255 && color.b == 0) {
            // Yellow to Red (0.75 - 1.0)
            return 0.75f + (1.0f - color.g * ratio255) * 0.25f;
        }
        else {
            // r,g,b 都不是255的情况，找出最大分量来决定区间
            unsigned char max_val = std::max({color.r, color.g, color.b});
            if (color.b == max_val) {
                // 偏蓝色区域 (0.0 - 0.25)
                return (color.g * ratio255) * 0.25f;
            }
            else if (color.g == max_val) {
                if (color.r <= color.b) {
                    // 偏青色区域 (0.25 - 0.5)
                    return 0.25f + (1.0f - color.b * ratio255) * 0.25f;
                }
                else {
                    // 偏黄色区域 (0.5 - 0.75)
                    return 0.5f + (color.r * ratio255) * 0.25f;
                }
            }
            else { // color.r == max_val
                // 偏红色区域 (0.75 - 1.0)
                return 0.75f + (1.0f - color.g * ratio255) * 0.25f;
            }
        }
    } break;
    case LUMINANCE: {
        // Convert RGB to grayscale using standard luminance weights
        // Y = 0.299R + 0.587G + 0.114B
        return (0.299f * color.r + 0.587f * color.g + 0.114f * color.b) * ratio255;
    } break;

    default: { // GRAY_SCALE:
        // 由于灰度颜色的 R=G=B，我们可以只取其中一个通道的值, 下面是平均值的方法
        static constexpr float ratio_total = ratio255 / 3.0f;
        // 将 0-255 的值转换回 0-1 的比率
        return (color.r + color.g + color.b) * ratio_total;
    }
    }

    // if color is not in switch
    return 0.0f;
}
} // namespace Phoenix