
#include "libglsimplify_material.h"

#include "entity/libglsimplify_entity.h"

#include "core/libglsimplify_program.h"

namespace gl_simplify {

    namespace material {

        Material::Material(GLuint texture_unit)
            : _texture_unit(texture_unit)
            , _texture_buffer()

            , _color(glm::vec4(1.0, 1.0, 1.0, 1.0))

            , _specular_strength(0.5f)
            , _specular_shininess(32)
        {
            // default texture with white color [has no effect on color]
            _texture_buffer.GetTexture().Bind(_texture_unit);
            
            _texture_buffer.GetTexture()
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR).UploadColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
                
            _texture_buffer.GetTexture().Unbind();
        }

        Material::~Material()
        {
        }

        void Material::SetTexture(const std::string &path)
        {
            _texture_buffer.GetTexture().Bind(_texture_unit);
            
            _texture_buffer.GetTexture()
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR).UploadImage(path);
                
            _texture_buffer.GetTexture().Unbind();
        }

        void Material::BindTexture()
        {
            _texture_buffer.GetTexture().Bind(_texture_unit);
        }

        void Material::UnbindTexture()
        {
            _texture_buffer.GetTexture().Unbind();
        }

        void Material::SetColor(const glm::vec4 &color)
        {
            _color = color;
        }

        const glm::vec4 &Material::GetColor()
        {
            return _color;
        }

        void Material::SetSpecularStrength(GLfloat specular_strength)
        {
            _specular_strength = specular_strength;
        }

        GLfloat Material::GetSpecularStrength()
        {
            return _specular_strength;
        }

        void Material::SetSpecularShininess(GLuint specular_shininess)
        {
            _specular_shininess = specular_shininess;
        }

        GLuint Material::GetSpecularShininess()
        {
            return _specular_shininess;
        }
    }
}
