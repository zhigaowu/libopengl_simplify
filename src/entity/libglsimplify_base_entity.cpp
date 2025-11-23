
#include "libglsimplify_base_entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl_simplify {

    namespace entity {

        static const GLint VERTEX_STRIDE = 8; // position(3) + normal(3) + texcoord(2)

        void BaseEntity::createDefaultArrays()
        {
            _vbo = new core::BufferArray(GL_ARRAY_BUFFER);
            _ebo = new core::BufferArray(GL_ELEMENT_ARRAY_BUFFER);
            _vao = new core::VertexArray();
        }

        void BaseEntity::configureDefaultVertexAttributes(const VertexDataBuffer &vertices, const IndexBuffer &indices)
        {
            // upload data and set data format
            _vao->Bind();

            _vbo->Bind();
            _vbo->Upload(vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);
            _vbo->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
            _vbo->SetAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, normal)));
            _vbo->SetAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, texcoord)));
            _vbo->Unbind();

            _ebo->Bind();
            _ebo->Upload(indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        }

        void BaseEntity::destroyArrays()
        {
            if (_vbo)
            {
                delete _vbo;
                _vbo = nullptr;
            }
            
            if (_ebo)
            {
                delete _ebo;
                _ebo = nullptr;
            }
            
            if (_vao)
            {
                delete _vao;
                _vao = nullptr;
            }
        }

        BaseEntity::BaseEntity(EntityType type)
            : core::NonCopyable()

            , _entity_type(type)

            , _vbo(nullptr)
            , _ebo(nullptr)
            , _vao(nullptr)

            , _index_count(0)

            , _color(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f))

            , _model(glm::translate(glm::mat4(1.0), glm::vec3(0.0f)))
        {
        }

        BaseEntity::~BaseEntity()
        {
            destroyArrays();
        }

        void BaseEntity::SetColor(const glm::vec4 &color)
        {
            _color = color;
        }

        void BaseEntity::Translate(const glm::vec3 &position)
        {
            _model = glm::translate(_model, position);
        }

        void BaseEntity::TranslateTo(const glm::vec3 &position)
        {
            _model = glm::translate(glm::mat4(1.0f), position);
        }

        void BaseEntity::Rotate(GLfloat degrees, const glm::vec3& axis)
        {
            _model = glm::rotate(_model, glm::radians(degrees), axis);
        }

        void BaseEntity::Scale(const glm::vec3 &size)
        {
            _model = glm::scale(_model, size);
        }
    }
}

