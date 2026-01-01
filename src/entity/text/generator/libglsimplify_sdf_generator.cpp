
#include "libglsimplify_sdf_generator.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace gl_simplify {

    namespace entity::text::generator {

        SDFGenerator::SDFGenerator(const SDFControl& sdf_control)
            : BaseGenerator()

            , _sdf_control(sdf_control)
        {
        }

        SDFGenerator::~SDFGenerator()
        {
        }

        core::Texture2DPtr SDFGenerator::GenerateTexture(wchar_t character, const unsigned char* bitmap, GLsizei width, GLsizei height)
        {
            // 生成 SDF
            std::vector<GLubyte> sdf_data = generateSDF(
                bitmap, 
                static_cast<int>(width), 
                static_cast<int>(height), 
                _sdf_control.sdf_spread
            );

            // 创建并返回纹理对象
            return BaseGenerator::GenerateTexture(character, sdf_data.data(), width, height);
        }

        std::vector<GLubyte> SDFGenerator::generateSDF(const unsigned char* bitmap, int width, int height, int spread)
        {
            std::vector<GLubyte> sdf(width * height);

            // 为每个像素计算签名距离场
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    GLfloat distance = calculateDistance(bitmap, width, height, x, y, spread);
                    
                    // 归一化到 0-255 范围
                    // 距离为 0 时映射到 128（0.5）
                    // 正距离（内部）映射到 128-255
                    // 负距离（外部）映射到 0-127
                    GLfloat normalized = (distance / static_cast<GLfloat>(spread) + 1.0f) * 0.5f;
                    normalized = std::max(0.0f, std::min(1.0f, normalized));
                    
                    sdf[y * width + x] = static_cast<GLubyte>(normalized * 255.0f);
                }
            }

            return sdf;
        }

        GLfloat SDFGenerator::calculateDistance(const unsigned char* bitmap, int width, int height, int x, int y, int max_distance)
        {
            GLubyte center_value = bitmap[y * width + x];
            bool center_inside = center_value > 127;

            GLfloat min_distance = static_cast<GLfloat>(max_distance);

            // 在以 (x, y) 为中心的正方形区域内搜索最近的边界
            for (int dy = -max_distance; dy <= max_distance; ++dy)
            {
                for (int dx = -max_distance; dx <= max_distance; ++dx)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    // 检查边界
                    if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                    {
                        continue;
                    }

                    GLubyte neighbor_value = bitmap[ny * width + nx];
                    bool neighbor_inside = neighbor_value > 127;

                    // 只关心与中心像素不同的像素（边界）
                    if (center_inside != neighbor_inside)
                    {
                        GLfloat distance = std::sqrt(static_cast<GLfloat>(dx * dx + dy * dy));
                        min_distance = std::min(min_distance, distance);
                    }
                }
            }

            // 如果中心在内部，距离为正；否则为负
            return center_inside ? min_distance : -min_distance;
        }

    }
}
