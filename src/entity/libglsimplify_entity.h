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

#include "core/libglsimplify_buffer_array.h"
#include "core/libglsimplify_vertex_array.h"

#include "shader/libglsimplify_vertex_shader.h"

#include "shader/libglsimplify_color_shader.h"
#include "shader/libglsimplify_texture_shader.h"

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
            shader::VertexShader* _vertex_shader;

        protected:
            shader::ColorShader* _color_shader;
            shader::TextureShader* _texture_shader;

        protected:
            core::Shader* _attatch_shader;

        protected:
            glm::mat4 _model_transform;
            
        public:
            explicit Entity(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            virtual ~Entity();

            const glm::mat4& GetModel() { return _model_transform; }
            core::Program& GetProgram() { return _program; }

            bool Create(GLchar* error, GLsizei error_length);
            void Destroy();

            void Translate(const glm::vec3& position);
            
            void Rotate(GLfloat degrees, const glm::vec3& axis);

            void Scale(const glm::vec3& size);

            bool Attach(const glm::vec4& color, GLchar* error, GLsizei error_length);
            bool Attach(const std::string& texture_file, GLchar* error, GLsizei error_length);

            virtual bool InitializeVertexShader(GLchar* error, GLsizei error_length);
            virtual bool Update(GLchar* error, GLsizei error_length) = 0;

            virtual void Draw();
            virtual void Render(Camera* camera);
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_ENTITY_H
