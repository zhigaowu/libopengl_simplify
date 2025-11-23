/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_skybox.h
 *
 *    Description:  sky box logic
 *                  reference: https://learnopengl.com/Advanced-OpenGL/Cubemaps
 *
 *        Version:  1.0
 *        Created:  2024-12-12 15:24:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_BACKGROUND_SKYBOX_H
#define GL_SIMPLIFY_RENDERER_BACKGROUND_SKYBOX_H

#include "entity/libglsimplify_base_entity.h"
#include "core/libglsimplify_texture_buffer.h"

namespace gl_simplify {

    namespace renderer::background {

        class SkyBox : public entity::BaseEntity {
        public:
            SkyBox();
            ~SkyBox();

            void Load(const std::string& path);

            void Render() override;

        private:
            core::TextureCubePtr _sky_texture;
        };

        using SkyBoxPtr = std::shared_ptr<SkyBox>;
    }

}

#define CreateSkyBox() CreateDefaultEntity(gl_simplify::renderer::background::SkyBox)

#endif // GL_SIMPLIFY_RENDERER_BACKGROUND_SKYBOX_H
