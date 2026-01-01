/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_simple_generator.h
 *
 *    Description:  Simple Font generator using FreeType
 *                  Generates simple textures for characters
 *
 *        Version:  1.0
 *        Created:  2026-01-29 11:10:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_SIMPLE_GENERATOR_H
#define GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_SIMPLE_GENERATOR_H

#include "libglsimplify_base_generator.h"

namespace gl_simplify {

    namespace entity::text::generator {

        class SimpleGenerator : public BaseGenerator {
        public:
            struct SimpleControl {

                SimpleControl()
                {
                }
            };

        public:
            explicit SimpleGenerator(const SimpleControl& simple_control = SimpleControl());
            ~SimpleGenerator();

            // 加载字体并生成简单纹理
            core::Texture2DPtr GenerateTexture(wchar_t character, const unsigned char* bitmap, GLsizei width, GLsizei height) override;

        private:
            SimpleControl _simple_control;
        };

        using SimpleGeneratorPtr = std::shared_ptr<SimpleGenerator>;

#define CreateSimpleGeneratorOf(...) CreateWithParameter(gl_simplify::entity::text::generator::SimpleGenerator, __VA_ARGS__)

    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_SIMPLE_GENERATOR_H
