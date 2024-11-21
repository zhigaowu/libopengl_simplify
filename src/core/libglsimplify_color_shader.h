/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_color_shader.h
 *
 *    Description:  shader logic
 *
 *        Version:  1.0
 *        Created:  2024-11-19 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_COLOR_SHADER_H
#define GL_SIMPLIFY_CORE_COLOR_SHADER_H

#include "libglsimplify_shader.h"

#include <glm/glm.hpp>

namespace gl_simplify {

    namespace core {

        // forward declaration
        class Program;

        class ColorShader : public Shader {
            glm::vec4 _color;

        public:
            explicit ColorShader(const glm::vec4& color = glm::vec4(0.6, 0.6, 0.6, 1.0));
            ~ColorShader();

            void SetColor(const glm::vec4& color);

            void Update(Program& program) override;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_COLOR_SHADER_H
