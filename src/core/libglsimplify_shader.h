/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_shader.h
 *
 *    Description:  shader logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_SHADER_H
#define GL_SIMPLIFY_CORE_SHADER_H

#include "libglsimplify_shader_source.h"

namespace gl_simplify {

    namespace core {

        class Shader : private NonCopyable {
        public:
            GLuint id;
            GLenum type;

        public:
            ShaderSource source;
            
        public:
            explicit Shader(GLenum shader_type, const std::string& source_code = "");
            virtual ~Shader();

            bool Compile(GLchar* error, GLsizei error_length);
        };
    }
}

#endif // GL_SIMPLIFY_CORE_SHADER_H
