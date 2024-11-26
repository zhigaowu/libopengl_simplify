/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_color_shader.h
 *
 *    Description:  color shader logic
 *
 *        Version:  1.0
 *        Created:  2024-11-19 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SHADER_COLOR_SHADER_H
#define GL_SIMPLIFY_SHADER_COLOR_SHADER_H

#include "core/libglsimplify_shader.h"

namespace gl_simplify {

    // forward declaration
    namespace entity {
        class Entity;
    }

    namespace shader {

        class ColorShader : public core::Shader {
            glm::vec4 _color;

        public:
            explicit ColorShader(entity::Entity* entity);
            ~ColorShader();

            void SetColor(const glm::vec4& color);

            void Update() override;
        };
    }
}

#endif // GL_SIMPLIFY_SHADER_COLOR_SHADER_H
