/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_vertex_shader.h
 *
 *    Description:  vertex shader logic
 *
 *        Version:  1.0
 *        Created:  2024-11-20 09:58:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_SHADER_VERTEX_SHADER_H
#define GL_SIMPLIFY_SHADER_VERTEX_SHADER_H

#include "core/libglsimplify_shader.h"

namespace gl_simplify {

    // forward declaration
    namespace entity {
        class Entity;
        class Camera;
    }

    namespace shader {

        class VertexShader : public core::Shader {
        public:
            static const std::string MODEL_VARIABLE_NAME;
            static const std::string VIEW_VARIABLE_NAME;
            static const std::string PROJECTION_VARIABLE_NAME;

        protected:
            entity::Entity* _entity;

            const entity::Camera* _camera;

        public:
            static GLint MaxVertexAttributesSupported();

        public:
            explicit VertexShader(entity::Entity* entity);
            virtual ~VertexShader();

            void SetCamera(const entity::Camera* camera);

            void Update() override;
        };
    }
}

#endif // GL_SIMPLIFY_SHADER_VERTEX_SHADER_H
