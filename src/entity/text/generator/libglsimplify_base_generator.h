/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_base_generator.h
 *
 *    Description:  base Font generator using FreeType
 *
 *        Version:  1.0
 *        Created:  2025-12-05 23:10:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_BASE_GENERATOR_H
#define GL_SIMPLIFY_ENTITY_TEXT_GENERATOR_BASE_GENERATOR_H

#include "core/libglsimplify_texture_buffer.h"

#include <map>

namespace gl_simplify {

    namespace entity::text::generator {

        class BaseGenerator : private core::NonCopyable {
        public:
            BaseGenerator();
            virtual ~BaseGenerator();

            core::Texture2DPtr LookupLoadedTexture(wchar_t character) const;

            // 加载字体并生成 SDF 纹理
            virtual core::Texture2DPtr GenerateTexture(wchar_t character, const unsigned char* bitmap, GLsizei width, GLsizei height);

        private:
            using CharacterTextures = std::map<wchar_t, core::Texture2DPtr>;
            CharacterTextures _character_textures;
        };

        using BaseGeneratorPtr = std::shared_ptr<BaseGenerator>;
    }
}

#endif // GL_SIMPLIFY_ENTITY_TEXT_FACTORY_SDF_FACTORY_H
