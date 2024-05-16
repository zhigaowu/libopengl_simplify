/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_shader_source.h
 *
 *    Description:  shader source logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_SHADER_SOURCE_H
#define GL_SIMPLIFY_CORE_SHADER_SOURCE_H

#include "glad/glad.h"

#include <sstream>

namespace gl_simplify {

    namespace core {

        class ShaderSource {
        public:
            explicit ShaderSource(const std::string& lines = "");
            ~ShaderSource();
            
            ShaderSource& operator << (const std::string& lines);

            std::string Code() const;

        public:
            ShaderSource(ShaderSource&&) = delete;
            ShaderSource& operator=(ShaderSource&&) = delete;

            ShaderSource(const ShaderSource&) = delete;
            ShaderSource& operator=(const ShaderSource&) = delete;
        
        private:
            std::stringstream _source_stream;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_PROGRAM_H
