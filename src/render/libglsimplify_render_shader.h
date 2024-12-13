/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_render_shader.h
 *
 *    Description:  render shader logic
 *
 *        Version:  1.0
 *        Created:  2024-11-28 11:15:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDER_RENDER_SHADER_H
#define GL_SIMPLIFY_RENDER_RENDER_SHADER_H

#include "core/libglsimplify_program.h"

#include "entity/libglsimplify_camera.h"

#include "light/libglsimplify_directional_light.h"
#include "light/libglsimplify_spot_light.h"

namespace gl_simplify {

    namespace render {

        class RenderShader : public core::NonCopyable {
        protected:
            core::Program _program;

        protected:
            core::Shader _vertex_shader;
            core::Shader _fragment_shader;

        public:
            RenderShader();
            virtual ~RenderShader();

            bool Build(GLchar* error, GLsizei error_length);

            void Use();

            virtual void UpdateCameraView(const entity::CameraPtr& camera) = 0;

            virtual void UpdateDirectionalLight(const light::DirectionalLightPtr& light) = 0;

            virtual void UpdatePointLights(const light::PointLights& lights) = 0;

            virtual void UpdateSpotLights(const light::SpotLights& lights) = 0;

            virtual void UpdateEntity(const entity::EntityPtr& entity) = 0;
        };

        using RenderShaderPtr = std::shared_ptr<RenderShader>;
        using SharedRenderShader = std::shared_ptr<RenderShader>;
    }
}

#endif // GL_SIMPLIFY_RENDER_RENDER_SHADER_H