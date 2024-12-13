/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_phong_shader.h
 *
 *    Description:  phong render shader logic
 *
 *        Version:  1.0
 *        Created:  2024-11-28 11:20:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDER_PHONG_SHADER_H
#define GL_SIMPLIFY_RENDER_PHONG_SHADER_H

#include "libglsimplify_render_shader.h"

namespace gl_simplify {

    namespace render {

        class PhongShader : public RenderShader {
        public:
            PhongShader();
            ~PhongShader();

            void UpdateCameraView(const entity::CameraPtr& camera) override;

            void UpdateDirectionalLight(const light::DirectionalLightPtr& light) override;

            void UpdatePointLights(const light::PointLights& lights) override;

            void UpdateSpotLights(const light::SpotLights& lights) override;

            void UpdateEntity(const entity::EntityPtr& entity) override;
        };

        using PhongShaderPtr = std::shared_ptr<PhongShader>;
        using SharedPhongShader = std::shared_ptr<PhongShader>;
    }
}

#define CreatePhongShader() CreateDefaultEntity(gl_simplify::render::PhongShader)

#endif // GL_SIMPLIFY_RENDER_PHONG_SHADER_H
