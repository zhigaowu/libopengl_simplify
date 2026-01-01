/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_free_type.h
 *
 *    Description:  FreeType wrapper for text rendering
 *
 *        Version:  1.0
 *        Created:  2025-11-29 16:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_FONT_FREE_TYPE_H
#define GL_SIMPLIFY_ENTITY_TEXT_FONT_FREE_TYPE_H

#include "libglsimplify_character_glyph.h"

#include "entity/text/generator/libglsimplify_base_generator.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

namespace gl_simplify {

    namespace entity::text::font {
        
        /*
         * https://learnopengl.com/In-Practice/Text-Rendering
         */
        
        struct FaceParameter {
            std::string font_path;

            GLuint font_height;

            FT_Long face_index;

            FaceParameter(const std::string& font_path_, GLuint font_height_ = 48, FT_Long face_index_ = 0)
                : font_path(font_path_), font_height(font_height_), face_index(face_index_)
            {
            }
        };

        class Face : private core::NonCopyable {
        public:
            explicit Face(const FaceParameter& parameter, FT_Face face);
            ~Face();

            const FaceParameter& GetParameter() const;

            FT_Face GetFTFace() const;

            CharacterGlyph LoadCharacter(FT_ULong char_code, const generator::BaseGeneratorPtr& generator, std::string* error_message = nullptr);

        private:
            FaceParameter _parameter;

        private:
            FT_Face _face;

        private:
            DISABLE_DEFAULT_CONSTRUCT(Face);
        };
        using FacePtr = std::shared_ptr<Face>;
        
        class FreeType : private core::NonCopyable {
        private:
            FreeType();

        public:
            ~FreeType();

            FacePtr LoadFace(const FaceParameter& parameter, std::string* error_message = nullptr);

        public:
            static FreeType& Instance();

        private:
            FT_Library _ft_library;

        private:
            using FaceHeightMap = std::map<GLuint, FacePtr>;
            using FaceFamilyMap = std::map<std::string, FaceHeightMap>;
            FaceFamilyMap _loaded_faces;
        };

    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_FONT_FREE_TYPE_H
