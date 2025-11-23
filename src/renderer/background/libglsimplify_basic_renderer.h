/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_basic_renderer.h
 *
 *    Description:  the background basic renderer
 *
 *        Version:  1.0
 *        Created:  2025-11-22 15:24:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_BACKGROUND_BASIC_RENDERER_H
#define GL_SIMPLIFY_RENDERER_BACKGROUND_BASIC_RENDERER_H

#include "renderer/libglsimplify_base_renderer.h"

namespace gl_simplify {

    namespace renderer::background {

        class BasicRenderer : public renderer::BaseRenderer {
        private:
            glm::vec4 _color;

        public:
            BasicRenderer();
            ~BasicRenderer();

            void SetColor(const glm::vec4& color);

            void Clear();

            void Render(const entity::BaseEntityPtr& entity) override;
        };

        using BasicRendererPtr = std::shared_ptr<BasicRenderer>;
    }
}

#define CreateBasicBackgroundRenderer() CreateDefault(gl_simplify::renderer::background::BasicRenderer)

#endif // GL_SIMPLIFY_RENDERER_BACKGROUND_BASIC_RENDERER_H
