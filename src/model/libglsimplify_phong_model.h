/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_phong_model.h
 *
 *    Description:  phong render model logic
 *
 *        Version:  1.0
 *        Created:  2024-11-28 11:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_MODEL_PHONG_MODEL_H
#define GL_SIMPLIFY_MODEL_PHONG_MODEL_H

#include "libglsimplify_render_model.h"

namespace gl_simplify {

    namespace model {

        class PhongModel : public RenderModel {
        public:
            PhongModel();
            ~PhongModel();

            void UpdateCameraView(entity::Camera* camera) override;

            void UpdateMaterial(material::SharedMaterial material) override;

            void UpdateDirectionalLight(light::DirectionalLight* light) override;

            void UpdatePointLightCount(GLint count) override;
            void UpdatePointLight(light::PointLight* light, GLint index) override;

            void UpdateSpotLightCount(GLint count) override;
            void UpdateSpotLight(light::SpotLight* light, GLint index) override;

            void Render(entity::Entity* entity) override;
        };
    }
}

#endif // GL_SIMPLIFY_MODEL_PHONG_MODEL_H
