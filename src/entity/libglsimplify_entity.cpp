
#include "libglsimplify_entity.h"

#include "material/libglsimplify_material_factory.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl_simplify {

    namespace entity {
        void Entity::updateNormalModel()
        {
            _normal_model = glm::mat3(glm::transpose(glm::inverse(_model)));
        }

        void Entity::createDefaultArrays()
        {
            _vbo = new core::BufferArray(GL_ARRAY_BUFFER);
            _ebo = new core::BufferArray(GL_ELEMENT_ARRAY_BUFFER);
            _vao = new core::VertexArray();
        }

        void Entity::bindDefaultVertexLayout()
        {
            // upload data and set data format
            _vao->Bind();

            _vbo->Bind();
            _vbo->Upload(sizeof(GLfloat) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
            _vbo->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, VERTEX_STRIDE_WITH_NORMAL_UV * sizeof(float), (void*)0);
            _vbo->SetAttribute(1, 3, GL_FLOAT, GL_FALSE, VERTEX_STRIDE_WITH_NORMAL_UV * sizeof(float), (void*)(3 * sizeof(float)));
            _vbo->SetAttribute(2, 2, GL_FLOAT, GL_FALSE, VERTEX_STRIDE_WITH_NORMAL_UV * sizeof(float), (void*)(6 * sizeof(float)));
            _vbo->Unbind();

            _ebo->Bind();
            _ebo->Upload(sizeof(GLuint) * _indices.size(), _indices.data(), GL_STATIC_DRAW);

            _vao->Unbind();
        }

        void Entity::destroyDefaultArrays()
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

        Entity::Entity(const glm::vec3& position)
            : _position(position)

            , _model(glm::translate(glm::mat4(1.0), position))
            , _normal_model()

            , _vertices()
            , _indices()

            , _vbo(nullptr)
            , _ebo(nullptr)
            , _vao(nullptr)

            , _material(material::MaterialFactory::Create(glm::vec4(1.0f), glm::vec4(1.0f), glm::vec4(1.0f), 32.0f))
        {
            updateNormalModel();
        }

        Entity::~Entity()
        {
            Destroy();
        }

        void Entity::Destroy()
        {
            destroyDefaultArrays();

            _material = nullptr;
        }

        void Entity::Attatch(material::SharedMaterial material)
        {
            if (material)
            {
                _material = material;
            }
        }

        void Entity::Translate(const glm::vec3 &position)
        {
            // transform matrix for render
            _model = glm::translate(_model, position);

            // position for entity-self
            _position += position;
        }

        void Entity::TranslateTo(const glm::vec3 &position)
        {
            Translate(position - _position);
        }

        void Entity::Rotate(GLfloat degrees, const glm::vec3& axis)
        {
            _model = glm::rotate(_model, glm::radians(degrees), axis);

            updateNormalModel();
        }

        void Entity::RotateAround(GLfloat degrees, const glm::vec3 &axis, const glm::vec3 &target)
        {
            // get rotation matrix
            glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), degrees, axis);

            // get local position in target coordinate system
            glm::vec4 position_to_target = rotation_matrix * glm::vec4(_position - target, 1.0f);

            // change local position back to world position
            glm::vec3 position_to_world = target + glm::vec3(position_to_target);

            // move
            Translate(position_to_world - _position);
        }

        void Entity::Scale(const glm::vec3 &size)
        {
            _model = glm::scale(_model, size);
            
            updateNormalModel();
        }

        void Entity::Render()
        {
            _material->BindTexture();

            _vao->Bind();

            glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
            
            _vao->Unbind();

            _material->UnbindTexture();
        }
    }
}

