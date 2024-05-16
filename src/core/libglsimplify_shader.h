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

#include <vector>

namespace gl_simplify {

    namespace core {

        class Shader {
        public:
            static GLint MaxVertexAttributesSupported();

        public:
            GLuint id;
            GLenum type;
            
        public:
            explicit Shader(GLenum shader_type = GL_VERTEX_SHADER);
            ~Shader();

            Shader& AddSource(const ShaderSource& source);

            bool Compile(GLchar* error, GLsizei error_length);

        public:
            Shader(Shader&&) = delete;
            Shader& operator=(Shader&&) = delete;

            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
        
        private:
            std::vector<std::string> _sources_code;
            std::vector<const char*> _sources_code_ref;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_SHADER_H
