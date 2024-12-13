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

#ifndef GL_SIMPLIFY_SCENE_SKYBOX_H
#define GL_SIMPLIFY_SCENE_SKYBOX_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace scene {

        class SkyBox : public entity::Entity {
        core::TextureBuffer _sky_texture_buffer;

        public:
            SkyBox(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~SkyBox();

            void Load(const std::string& path);

            void Create() override;

            void Render() override;
        };

        using SkyBoxPtr = std::shared_ptr<SkyBox>;
    }

}

#define CreateSkyBox() CreateDefaultEntity(gl_simplify::scene::SkyBox)

#endif // GL_SIMPLIFY_SCENE_SKYBOX_H
