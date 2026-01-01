/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_sdf_generator.h
 *
 *    Description:  SDF Font generator using FreeType
 *                  Generates signed distance field textures for characters
 *
 *        Version:  1.0
 *        Created:  2025-11-29 23:10:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_SDF_GENERATOR_H
#define GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_SDF_GENERATOR_H

#include "libglsimplify_base_generator.h"

namespace gl_simplify {

    namespace entity::text::generator {

        class SDFGenerator : public BaseGenerator {
        public:
            struct SDFControl {
                GLint sdf_spread;          // SDF 扩散半径（像素）

                GLfloat smoothness;        // 边缘平滑度（0.0 - 1.0）
                GLfloat outline_width;     // 轮廓宽度（0.0 - 0.5）

                glm::vec4 outline_color;   // 轮廓颜色

                SDFControl()
                    : sdf_spread(8)
                    , smoothness(0.05f)
                    , outline_width(0.0f)
                    , outline_color(0.0f, 0.0f, 0.0f, 1.0f)
                {
                }
            };

        public:
            explicit SDFGenerator(const SDFControl& sdf_control = SDFControl());
            ~SDFGenerator();

            // 加载字体并生成 SDF 纹理
            core::Texture2DPtr GenerateTexture(wchar_t character, const unsigned char* bitmap, GLsizei width, GLsizei height) override;

            GLfloat GetSmoothness() const { return _sdf_control.smoothness; }
            GLfloat GetOutlineWidth() const { return _sdf_control.outline_width; }
            glm::vec4 GetOutlineColor() const { return _sdf_control.outline_color; }

        private:
            // 从位图生成 SDF
            std::vector<GLubyte> generateSDF(const unsigned char* bitmap, int width, int height, int spread);

            // 计算距离场
            GLfloat calculateDistance(const unsigned char* bitmap, int width, int height, int x, int y, int max_distance);

        private:
            SDFControl _sdf_control;
        };

        using SDFGeneratorPtr = std::shared_ptr<SDFGenerator>;

#define CreateSDFGeneratorOf(...) CreateWithParameter(gl_simplify::entity::text::generator::SDFGenerator, __VA_ARGS__)

    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_SDF_GENERATOR_H
