/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_texture_renderer.h
 *
 *    Description:  texture render model logic
 *
 *        Version:  1.0
 *        Created:  2025-11-23 19:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_FOREGROUND_TEXTURE_RENDERER_H
#define GL_SIMPLIFY_RENDERER_FOREGROUND_TEXTURE_RENDERER_H

#include "libglsimplify_basic_renderer.h"

namespace gl_simplify {

    namespace renderer::foreground {

        class TextureRenderer : public BasicRenderer {
        public:
            TextureRenderer();
            ~TextureRenderer();

            void Render(const entity::BaseEntityPtr& entity) override;
        };

        using TextureRendererPtr = std::shared_ptr<TextureRenderer>;
    }
}

#define CreateTextureForegroundRenderer() CreateDefaultEntity(gl_simplify::renderer::foreground::TextureRenderer)

#endif // GL_SIMPLIFY_RENDERER_FOREGROUND_TEXTURE_RENDERER_H
