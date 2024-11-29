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

            void UpdateAmbient(const glm::vec4& ambient) override;
            void UpdateLight(light::Light* light) override;

            void Render(entity::Entity* entity) override;
        };
    }
}

#endif // GL_SIMPLIFY_MODEL_PHONG_MODEL_H
