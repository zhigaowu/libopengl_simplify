/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_render_model.h
 *
 *    Description:  render model logic
 *
 *        Version:  1.0
 *        Created:  2024-11-28 11:15:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_MODEL_RENDER_MODEL_H
#define GL_SIMPLIFY_MODEL_RENDER_MODEL_H

#include "core/libglsimplify_program.h"

#include "entity/libglsimplify_camera.h"
#include "light/libglsimplify_light.h"
#include "material/libglsimplify_material.h"

namespace gl_simplify {

    namespace model {

        class RenderModel : public core::NonCopyable {
        protected:
            core::Program _program;

        protected:
            core::Shader _vertex_shader;
            core::Shader _fragment_shader;

        public:
            RenderModel();
            virtual ~RenderModel();

            bool Build(GLchar* error, GLsizei error_length);

            void Use();

            virtual void UpdateCameraView(entity::Camera* camera) = 0;

            virtual void UpdateLight(light::Light* light) = 0;
            virtual void UpdateMaterial(material::SharedMaterial material) = 0;

            virtual void Render(entity::Entity* entity) = 0;
        };
    }
}

#endif // GL_SIMPLIFY_MODEL_RENDER_MODEL_H