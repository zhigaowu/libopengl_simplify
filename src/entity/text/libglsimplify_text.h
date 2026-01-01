/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_text.h
 *
 *    Description:  text string entity
 *
 *        Version:  1.0
 *        Created:  2025-11-29 17:30:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_TEXT_H
#define GL_SIMPLIFY_ENTITY_TEXT_TEXT_H

#include "libglsimplify_character.h"

#include "generator/libglsimplify_base_generator.h"

#include "font/libglsimplify_free_type.h"

namespace gl_simplify {

    namespace entity::text {

        struct TextParameter {
            std::string font_path;
            // 字体尺寸【设计尺寸，通常为字体的原始设计大小，建议大小： 48 128 256】
            GLuint font_height;
            GLboolean render_both_faces;

            TextParameter()
                : font_path("")
                , font_height(128)
                , render_both_faces(GL_FALSE)
            {
            }
        };

        class Text : public BaseEntity {
        private:
            std::wstring _text;
            // 字体像素大小【渲染大小】
            GLuint _pixel_size;

        private:
            TextParameter _parameter;

        private:
            font::FacePtr _face;

        private:
            Characters _characters;

        public:
            explicit Text(const std::wstring& text, GLuint pixel_size = 48, const TextParameter& parameter = TextParameter());
            ~Text();

            bool Generate(const generator::BaseGeneratorPtr& generator, std::string* error_message = nullptr);
            
            const std::wstring& GetText() const;

            GLuint GetPixelSize() const;

            const Characters& GetCharacters() const;

            void Render() override;
        };

        using TextPtr = std::shared_ptr<Text>;

#define CreateTextOf(...) CreateWithParameter(gl_simplify::entity::text::Text, __VA_ARGS__)

    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_TEXT_H
