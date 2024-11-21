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

#include "libglsimplify_types.h"

#include <sstream>

namespace gl_simplify {

    namespace core {

        class ShaderSource : private NonCopyable {
        public:
            explicit ShaderSource(const std::string& source = "");
            ~ShaderSource();

            ShaderSource& operator << (const char* source);
            ShaderSource& operator << (const std::string& source);

            std::string Source() const;
        
        private:
            std::stringstream _source_stream;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_PROGRAM_H
