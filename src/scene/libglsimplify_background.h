/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_background.h
 *
 *    Description:  the scene background
 *
 *        Version:  1.0
 *        Created:  2024-11-20 15:24:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SCENE_BACKGROUND_H
#define GL_SIMPLIFY_SCENE_BACKGROUND_H

#include "libglsimplify_skybox.h"

#include "model/libglsimplify_render_model.h"

namespace gl_simplify {

    namespace scene {

        class Background : public model::RenderModel {
        private:
            glm::vec4 _color;

        private:
            SkyBoxPtr _sky_box;

        public:
            Background();
            ~Background();

            void SetColor(const glm::vec4& color);

            void Clear();

            bool LoadSkyBox(const std::string& path, GLchar* error, GLsizei error_length);

            void Render();

            void UpdateCameraView(const entity::CameraPtr& camera) override;

            void UpdateDirectionalLight(const light::DirectionalLightPtr& light) override;

            void UpdatePointLights(const light::PointLights& lights) override;

            void UpdateSpotLights(const light::SpotLights& lights) override;

            void UpdateEntity(const entity::EntityPtr& entity) override;
        };
    }
}

#endif // GL_SIMPLIFY_SCENE_BACKGROUND_H
