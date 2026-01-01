/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_simple_text_renderer.h
 *
 *    Description:  Simple Text Renderer with shader support
 *
 *        Version:  1.0
 *        Created:  2026-01-01 10:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_TEXT_SIMPLE_TEXT_RENDERER_H
#define GL_SIMPLIFY_RENDERER_TEXT_SIMPLE_TEXT_RENDERER_H

#include "libglsimplify_base_text_renderer.h"

namespace gl_simplify {

    namespace renderer::text {

        class SimpleTextRenderer : public BaseTextRenderer {
        public:
            SimpleTextRenderer();
            ~SimpleTextRenderer() override;

        protected:
            void updateShaderProgram() override;
        };

        using SimpleTextRendererPtr = std::shared_ptr<SimpleTextRenderer>;

    }
}

#define CreateSimpleTextRenderer() CreateDefaultEntity(gl_simplify::renderer::text::SimpleTextRenderer)

#endif // GL_SIMPLIFY_RENDERER_TEXT_SIMPLE_TEXT_RENDERER_H