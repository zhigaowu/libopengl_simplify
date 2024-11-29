
#include "libglsimplify_material.h"

#include "entity/libglsimplify_entity.h"

#include "core/libglsimplify_program.h"

namespace gl_simplify {

    namespace material {
        void Material::generateDefaultTexture()
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

        Material::Material(GLfloat shininess)
            : _texture_unit(GL_TEXTURE0)
            , _texture_buffer()

            , _ambient(1.0f, 1.0f, 1.0f, 1.0f)
            , _diffuse(1.0f, 1.0f, 1.0f, 1.0f)
            , _specular(1.0f, 1.0f, 1.0f, 1.0f)

            , _shininess(shininess)
        {
            generateDefaultTexture();
        }

        Material::Material(const glm::vec4& ambient, GLfloat shininess)
            : _texture_unit(GL_TEXTURE0)
            , _texture_buffer()

            , _ambient(ambient)
            , _diffuse(1.0f, 1.0f, 1.0f, 1.0f)
            , _specular(1.0f, 1.0f, 1.0f, 1.0f)

            , _shininess(shininess)
        {
            generateDefaultTexture();
        }

        Material::Material(const glm::vec4& ambient, const glm::vec4& diffuse, GLfloat shininess)
            : _texture_unit(GL_TEXTURE0)
            , _texture_buffer()

            , _ambient(ambient)
            , _diffuse(diffuse)
            , _specular(1.0f, 1.0f, 1.0f, 1.0f)

            , _shininess(shininess)
        {
            generateDefaultTexture();
        }

        Material::Material(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, GLfloat shininess)
            : _texture_unit(GL_TEXTURE0)
            , _texture_buffer()

            , _ambient(ambient)
            , _diffuse(diffuse)
            , _specular(specular)

            , _shininess(shininess)
        {
            generateDefaultTexture();
        }

        Material::Material(const std::string& path, GLuint texture_unit)
            : _texture_unit(texture_unit)
            , _texture_buffer()

            , _ambient(1.0f, 1.0f, 1.0f, 1.0f)
            , _diffuse(1.0f, 1.0f, 1.0f, 1.0f)
            , _specular(1.0f, 1.0f, 1.0f, 1.0f)

            , _shininess(32.0f)
        {
            SetTexture(path);
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

        void Material::SetAmbient(const glm::vec4& ambient)
        {
            _ambient = ambient;
        }

        const glm::vec4 &Material::GetAmbient()
        {
            return _ambient;
        }

        void Material::SetDiffuse(const glm::vec4& diffuse)
        {
            _diffuse = diffuse;
        }

        const glm::vec4 &Material::GetDiffuse()
        {
            return _diffuse;
        }

        void Material::SetSpecular(const glm::vec4& specular)
        {
            _specular = specular;
        }

        const glm::vec4 &Material::GetSpecular()
        {
            return _specular;
        }

        void Material::SetShininess(GLfloat shininess)
        {
            _shininess = shininess;
        }

        GLfloat Material::GetShininess()
        {
            return _shininess;
        }

        void Material::Copy(Material *other)
        {
            if (other)
            {
                _shininess = other->_shininess;

                _ambient = other->_ambient;
                _diffuse = other->_diffuse;
                _specular = other->_specular;
            }
        }
    }
}
