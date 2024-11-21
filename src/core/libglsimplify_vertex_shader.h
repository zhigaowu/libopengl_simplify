/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_vertex_shader.h
 *
 *    Description:  vertex shader
 *
 *        Version:  1.0
 *        Created:  2024-11-20 09:58:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_VERTEX_SHADER_H
#define GL_SIMPLIFY_CORE_VERTEX_SHADER_H

#include "libglsimplify_shader.h"

#include <glm/glm.hpp>

namespace gl_simplify {

    namespace core {

        // forward declaration
        class Program;

        class VertexShader : public Shader {
        public:
            static GLint MaxVertexAttributesSupported();

        public:
            VertexShader();
            virtual ~VertexShader();
        };
    }
}

#endif // GL_SIMPLIFY_CORE_VERTEX_SHADER_H
