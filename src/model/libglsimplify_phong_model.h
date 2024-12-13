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

            void UpdateCameraView(const entity::CameraPtr& camera) override;

            void UpdateDirectionalLight(const light::DirectionalLightPtr& light) override;

            void UpdatePointLights(const light::PointLights& lights) override;

            void UpdateSpotLights(const light::SpotLights& lights) override;

            void UpdateEntity(const entity::EntityPtr& entity) override;
        };
    }
}

#endif // GL_SIMPLIFY_MODEL_PHONG_MODEL_H
