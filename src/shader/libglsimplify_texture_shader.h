/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_texture_shader.h
 *
 *    Description:  texture shader logic
 *
 *        Version:  1.0
 *        Created:  2024-11-22 16:00:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SHADER_TEXTURE_SHADER_H
#define GL_SIMPLIFY_SHADER_TEXTURE_SHADER_H

#include "core/libglsimplify_shader.h"

#include "core/libglsimplify_texture_buffer.h"

namespace gl_simplify {

    // forward declaration
    namespace entity {
        class Entity;
    }

    namespace shader {

        class TextureShader : public core::Shader {
            GLuint _texture_unit;
            core::TextureBuffer _texture_buffer;

        public:
            explicit TextureShader(entity::Entity* entity, GLuint texture_unit = GL_TEXTURE0);
            ~TextureShader();

            void SetFile(const std::string& path);

            void Update() override;
        
        private:
            TextureShader() = delete;
        };
    }
}

#endif // GL_SIMPLIFY_SHADER_TEXTURE_SHADER_H
