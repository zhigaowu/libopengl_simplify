/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_sdf_text_renderer.h
 *
 *    Description:  SDF Text Renderer with shader support
 *                  Implements Valve's signed distance field text rendering
 *
 *        Version:  1.0
 *        Created:  2025-11-29 17:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_TEXT_SDF_TEXT_RENDERER_H
#define GL_SIMPLIFY_RENDERER_TEXT_SDF_TEXT_RENDERER_H

#include "libglsimplify_base_text_renderer.h"

namespace gl_simplify {

    namespace renderer::text {

        class SDFTextRenderer : public BaseTextRenderer {
        public:
            SDFTextRenderer();
            ~SDFTextRenderer() override;

        protected:
            void updateShaderProgram() override;
        };

        using SDFTextRendererPtr = std::shared_ptr<SDFTextRenderer>;

    }
}

#define CreateSDFTextRenderer() CreateDefaultEntity(gl_simplify::renderer::text::SDFTextRenderer)

#endif // GL_SIMPLIFY_RENDERER_TEXT_SDF_TEXT_RENDERER_H
