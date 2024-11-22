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

#ifndef GL_SIMPLIFY_CORE_TEXTURE_SHADER_H
#define GL_SIMPLIFY_CORE_TEXTURE_SHADER_H

#include "libglsimplify_shader.h"

#include "libglsimplify_texture_buffer.h"

#include <glm/glm.hpp>

namespace gl_simplify {

    namespace core {

        // forward declaration
        class Program;

        class TextureShader : public Shader {
            GLuint _texture_unit;
            TextureBuffer _texture_buffer;

        public:
            explicit TextureShader(Program& program, GLuint texture_unit = GL_TEXTURE0);
            ~TextureShader();

            void SetFile(const std::string& path);

            void Update() override;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_TEXTURE_SHADER_H
