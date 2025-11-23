/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_basic_renderer.h
 *
 *    Description:  basic render model logic
 *
 *        Version:  1.0
 *        Created:  2025-11-22 11:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_FOREGROUND_BASIC_RENDERER_H
#define GL_SIMPLIFY_RENDERER_FOREGROUND_BASIC_RENDERER_H

#include "renderer/libglsimplify_base_renderer.h"

namespace gl_simplify {

    namespace renderer::foreground {

        class BasicRenderer : public BaseRenderer {
        public:
            BasicRenderer();
            ~BasicRenderer();

            void Render(const entity::BaseEntityPtr& entity) override;
        };

        using BasicRendererPtr = std::shared_ptr<BasicRenderer>;
    }
}

#define CreateBasicForegroundRenderer() CreateDefaultEntity(gl_simplify::renderer::foreground::BasicRenderer)

#endif // GL_SIMPLIFY_RENDER_FOREGROUND_BASIC_RENDERER_H
