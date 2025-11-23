/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_base_renderer.h
 *
 *    Description:  base renderer
 *
 *        Version:  1.0
 *        Created:  2025-11-22 13:15:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_RENDERER_BASE_RENDERER_H
#define GL_SIMPLIFY_RENDERER_BASE_RENDERER_H

#include "core/libglsimplify_program.h"

#include "camera/libglsimplify_base_camera.h"

namespace gl_simplify {

    namespace renderer {

        class BaseRenderer : public core::NonCopyable {
        protected:
            core::Program _program;

        protected:
            core::Shader _vertex_shader;
            core::Shader _fragment_shader;

        public:
            BaseRenderer();
            virtual ~BaseRenderer();

            virtual bool Build(GLchar* error, GLsizei error_length);

            virtual void Use();

            virtual void BindCamera(const camera::BaseCameraPtr& camera);

            virtual void Render(const entity::BaseEntityPtr& entity);
        };

        using BaseRendererPtr = std::shared_ptr<BaseRenderer>;
    }
}

#endif // GL_SIMPLIFY_RENDER_RENDER_MODEL_H