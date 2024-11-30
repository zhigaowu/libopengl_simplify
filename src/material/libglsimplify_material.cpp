
#include "libglsimplify_material.h"

#include "entity/libglsimplify_entity.h"

#include "core/libglsimplify_program.h"

namespace gl_simplify {

    namespace material {

        static const GLint MAP_SIZE = 2;

        static const GLint DIFFUSE_MAP_INDEX = 0;
        static const GLint SPECULAR_MAP_INDEX = 1;

        static const GLuint DIFFUSE_MAP_UNIT = GL_TEXTURE0;
        static const GLuint SPECULAR_MAP_UNIT = GL_TEXTURE1;

        Material::Material(GLfloat shininess)
            : _texture_buffer(MAP_SIZE)

            , _shininess(shininess)
        {
            SetDiffuse(glm::vec4(1.0f));
            SetSpecular(glm::vec4(1.0f));
        }

        Material::Material(const glm::vec4&, const glm::vec4& diffuse, const glm::vec4& specular, GLfloat shininess)
            : _texture_buffer(MAP_SIZE)

            , _shininess(shininess)
        {
            SetDiffuse(diffuse);
            SetSpecular(specular);
        }

        Material::Material(const std::string& diffuse_map_path, const std::string& specular_map_path, GLfloat shininess)
            : _texture_buffer(MAP_SIZE)

            , _shininess(shininess)
        {
            // diffuse map
            SetDiffuseMap(diffuse_map_path);

            // specular map
            SetSpecularMap(specular_map_path);
        }

        Material::~Material()
        {
        }

        void Material::SetDiffuseMap(const std::string &path)
        {
            core::TextureBuffer::Texture& texture = _texture_buffer.GetTexture(DIFFUSE_MAP_INDEX);
            
            texture.Bind(DIFFUSE_MAP_UNIT);
            
            texture.UploadImage(path)
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
            texture.Unbind();
        }

        void Material::SetSpecularMap(const std::string &path)
        {
            core::TextureBuffer::Texture& texture = _texture_buffer.GetTexture(SPECULAR_MAP_INDEX);
            
            texture.Bind(SPECULAR_MAP_UNIT);
            
            texture.UploadImage(path)
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
            texture.Unbind();
        }

        void Material::BindTexture()
        {
            _texture_buffer.GetTexture(DIFFUSE_MAP_INDEX).Bind(DIFFUSE_MAP_UNIT);
            _texture_buffer.GetTexture(SPECULAR_MAP_INDEX).Bind(SPECULAR_MAP_UNIT);
        }

        void Material::UnbindTexture()
        {
            _texture_buffer.GetTexture(DIFFUSE_MAP_INDEX).Unbind();
            _texture_buffer.GetTexture(SPECULAR_MAP_INDEX).Unbind();
        }

        void Material::SetDiffuse(const glm::vec4& diffuse)
        {
            core::TextureBuffer::Texture& texture = _texture_buffer.GetTexture(DIFFUSE_MAP_INDEX);
            
            // diffuse map
            texture.Bind(DIFFUSE_MAP_UNIT);
            
            texture.UploadColor(diffuse)
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
            texture.Unbind();
        }

        GLuint Material::GetDiffuse()
        {
            return DIFFUSE_MAP_UNIT - GL_TEXTURE0;
        }

        void Material::SetSpecular(const glm::vec4& specular)
        {
            core::TextureBuffer::Texture& texture = _texture_buffer.GetTexture(SPECULAR_MAP_INDEX);
            
            // specular map
            texture.Bind(SPECULAR_MAP_UNIT);
            
            texture.UploadColor(specular)
                .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
            texture.Unbind();
        }

        GLuint Material::GetSpecular()
        {
            return SPECULAR_MAP_UNIT - GL_TEXTURE0;
        }

        void Material::SetShininess(GLfloat shininess)
        {
            _shininess = shininess;
        }

        GLfloat Material::GetShininess()
        {
            return _shininess;
        }
    }
}
