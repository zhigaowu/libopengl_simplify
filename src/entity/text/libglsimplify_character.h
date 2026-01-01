/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_character.h
 *
 *    Description:  character entity
 *
 *        Version:  1.0
 *        Created:  2025-11-29 17:00:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_CHARACTER_H
#define GL_SIMPLIFY_ENTITY_TEXT_CHARACTER_H

#include "entity/libglsimplify_base_entity.h"

#include "font/libglsimplify_character_glyph.h"

namespace gl_simplify {

    namespace entity::text {

        class Character : public BaseEntity {
        private:
            wchar_t _character;

        private:
            // 字符信息
            font::CharacterGlyph _character_glyph;

        public:
            explicit Character(const font::CharacterGlyph& character_glyph, wchar_t character = 0, bool render_both_faces = false);
            ~Character();

            wchar_t GetCharacter() const;

            void Render() override;
        };

#define CreateCharacterOf(...) CreateWithParameter(gl_simplify::entity::text::Character, __VA_ARGS__)

        using CharacterPtr = std::shared_ptr<Character>;
        using Characters = std::vector<CharacterPtr>;

    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_CHARACTER_H
