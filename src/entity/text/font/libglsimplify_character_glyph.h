/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_character_glyph.h
 *
 *    Description:  character glyph definition
 *
 *        Version:  1.0
 *        Created:  2025-11-29 17:00:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_FONT_CHARACTER_GLYPH_H
#define GL_SIMPLIFY_ENTITY_TEXT_FONT_CHARACTER_GLYPH_H

#include "core/libglsimplify_texture_buffer.h"

namespace gl_simplify {

    namespace entity::text::font {

        struct CharacterGlyph {
            glm::ivec2 size;            // 字形大小
            glm::ivec2 bearing;         // 从基线到字形左侧/顶部的偏移
            GLuint advance;             // 到下一个字形的水平距离

            core::Texture2DPtr texture; // 字形纹理

            CharacterGlyph()
                : size(0, 0)
                , bearing(0, 0)
                , advance(0)
                , texture(nullptr)
            {
            }
        };

    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_FONT_CHARACTER_GLYPH_H
