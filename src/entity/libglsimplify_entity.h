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

#include "core/libglsimplify_buffer_array.h"
#include "core/libglsimplify_vertex_array.h"

#include "material/libglsimplify_material.h"

namespace gl_simplify {

    namespace entity {

        constexpr const GLsizei VERTEX_STRIDE_WITH_NORMAL_UV = 8; // Positions(3) Normals(3) Texture Coords(2)

        class Entity : private core::NonCopyable {
        protected:
            glm::vec3 _position;
            glm::mat4 _model;
            glm::mat3 _normal_model;

        protected:
            std::vector<GLfloat> _vertices;
            std::vector<GLuint> _indices;

        protected:
            core::BufferArray* _vbo;
            core::BufferArray* _ebo;
            core::VertexArray* _vao;

        protected:
            material::SharedMaterial _material;

        protected:
            void updateNormalModel();

        protected:
            void createDefaultArrays();
            void bindDefaultVertexLayout();
            void destroyDefaultArrays();
            
        public:
            explicit Entity(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            virtual ~Entity();

            const glm::vec3& GetPosition() { return _position; }
            const glm::mat4& GetModel() { return _model; }
            const glm::mat3& GetNormalModel() { return _normal_model; }

            material::SharedMaterial& GetMaterial() { return _material; }

            void Attatch(material::SharedMaterial material);

            void Translate(const glm::vec3& position);

            void TranslateTo(const glm::vec3& position);
            
            void Rotate(GLfloat degrees, const glm::vec3& axis);

            void Scale(const glm::vec3& size);

            virtual void Create() = 0;

            virtual void Destroy();

            virtual void Render();
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_ENTITY_H
