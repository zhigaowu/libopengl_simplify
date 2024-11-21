
#include "libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        Entity::Entity(const glm::vec3& position)
            : _position(position)
            
            , _program()
            
            , _vertex_shader(nullptr)

            , _color_shader(nullptr)

            , _attatch_shader(nullptr)

            , _model_transform(glm::translate(glm::mat4(1.0), position))
        {
        }

        Entity::~Entity()
        {
            if (_color_shader)
            {
                delete _color_shader;
                _color_shader = nullptr;
            }
        }

        void Entity::Move(const glm::vec3& position)
        {
            // transform matrix for render
            _model_transform = glm::translate(_model_transform, position);

            // position for entity-self
            _position += position;
        }

        void Entity::Rotate(GLfloat degrees, const glm::vec3& axis)
        {
            _model_transform = glm::rotate(_model_transform, glm::radians(degrees), axis);
        }

        void Entity::Scale(const glm::vec3 &size)
        {
            _model_transform = glm::scale(_model_transform, size);
        }

        bool Entity::Attach(const glm::vec4 &color, GLchar* error, GLsizei error_length)
        {
            bool linked = true;

            // create new color attach
            if (!_color_shader)
            {
                _color_shader = new core::ColorShader(color);

                if ((linked = _color_shader->Compile(error, error_length)))
                {
                    linked = _program.Attach(*_vertex_shader).Attach(*_color_shader).Link(error, error_length);
                }
            }

            if (linked)
            {
                _color_shader->SetColor(color);
            }

            _attatch_shader = _color_shader;

            return linked;
        }

        /*bool Entity::Attach(const core::TextureBuffer::Texture &texture, GLchar* error, GLsizei error_length)
        {
            Detach();

            _attatch_shader = new core::ColorShader(color);

            return false;
        }*/
       
    }
}

