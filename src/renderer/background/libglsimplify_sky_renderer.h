/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_sky_renderer.h
 *
 *    Description:  the sky renderer
 *
 *        Version:  1.0
 *        Created:  2025-11-22 15:24:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_BACKGROUND_SKY_RENDER_H
#define GL_SIMPLIFY_RENDERER_BACKGROUND_SKY_RENDER_H

#include "libglsimplify_skybox.h"

#include "libglsimplify_basic_renderer.h"

namespace gl_simplify {

    namespace renderer::background {

        class SkyRenderer : public BasicRenderer {
        private:
            SkyBoxPtr _sky_box;

        public:
            SkyRenderer();
            ~SkyRenderer();

            bool LoadSkyBox(const std::string& path, GLchar* error, GLsizei error_length);

            void Render(const entity::BaseEntityPtr& entity) override;
        };

        using SkyRendererPtr = std::shared_ptr<SkyRenderer>;
    }
}

#endif // GL_SIMPLIFY_RENDERER_BACKGROUND_SKY_RENDER_H
