
#include "libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        Entity::Entity(const glm::vec3& position)
            : _position(position)
            
            , _program()
            
            , _vertex_shader(nullptr)

            , _color_shader(nullptr)
            , _texture_shader(nullptr)

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

            if (_texture_shader)
            {
                delete _texture_shader;
                _texture_shader = nullptr;
            }
        }

        void Entity::Translate(const glm::vec3& position)
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
                _color_shader = new core::ColorShader(_program);

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

        bool Entity::Attach(const std::string& texture_file, GLchar* error, GLsizei error_length)
        {
            bool linked = true;

            // create new color attach
            if (!_texture_shader)
            {
                _texture_shader = new core::TextureShader(_program);

                if ((linked = _texture_shader->Compile(error, error_length)))
                {
                    linked = _program.Attach(*_vertex_shader).Attach(*_texture_shader).Link(error, error_length);
                }
            }

            if (linked)
            {
                _texture_shader->SetFile(texture_file);
            }

            _attatch_shader = _texture_shader;

            return linked;
        }
       
    }
}

