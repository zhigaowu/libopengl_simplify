/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_entity.h
 *
 *    Description:  base class for entity in the scene
 *
 *        Version:  1.0
 *        Created:  2024-11-19 14:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_ENTITY_H
#define GL_SIMPLIFY_ENTITY_ENTITY_H

#include "core/libglsimplify_program.h"

#include "core/libglsimplify_vertex_shader.h"

#include "core/libglsimplify_color_shader.h"
#include "core/libglsimplify_texture_shader.h"

#include "core/libglsimplify_buffer_array.h"
#include "core/libglsimplify_vertex_array.h"

namespace gl_simplify {

    namespace entity {

        // forward declaration
        class Camera;

        class Entity : private core::NonCopyable {
        protected:
            glm::vec3 _position;

        protected:
            core::Program _program;

        protected:
            core::VertexShader* _vertex_shader;

        protected:
            core::ColorShader* _color_shader;
            core::TextureShader* _texture_shader;

        protected:
            core::Shader* _attatch_shader;

        protected:
            glm::mat4 _model_transform;
            
        public:
            explicit Entity(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            virtual ~Entity();

            void Translate(const glm::vec3& position);
            
            void Rotate(GLfloat degrees, const glm::vec3& axis);

            void Scale(const glm::vec3& size);

            virtual bool Initialize(GLchar* error, GLsizei error_length) = 0;

            bool Attach(const glm::vec4& color, GLchar* error, GLsizei error_length);
            bool Attach(const std::string& texture_file, GLchar* error, GLsizei error_length);

            virtual void Render(Camera* camera) = 0;
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_ENTITY_H
