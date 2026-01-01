
#include "libglsimplify_texture_buffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace gl_simplify {

    namespace core {

        Texture::Texture(GLenum texture_type)
            : NonCopyable()

            , _self_generated(true)

            , _gl_unit(GL_TEXTURE0)

            , _gl_id(0)
            , _gl_type(texture_type)

            , _format()
        {
            glGenTextures(1, &_gl_id);
        }

        Texture::Texture(GLObjectID gl_id, GLenum texture_type)
            : NonCopyable()

            , _self_generated(false)

            , _gl_id(gl_id)
            , _gl_type(texture_type)

            , _format()
        {
        }

        Texture::~Texture()
        {
            if (_self_generated) 
            {
                glDeleteTextures(1, &_gl_id);
            }
        }

        Texture* Texture::SetUnit(GLuint texture_unit)
        {
            _gl_unit = texture_unit;

            return this;
        }

        Texture *Texture::ActiveUnit()
        {
            glActiveTexture(_gl_unit);
            
            return this;
        }

        Texture* Texture::Bind()
        {
            glBindTexture(_gl_type, _gl_id);

            return this;
        }

        void Texture::Unbind()
        {
            glBindTexture(_gl_type, 0);
        }

        Texture* Texture::SetParameter(GLenum pname, GLint pvalue)
        {
            glTexParameteri(_gl_type, pname, pvalue);

            return this;
        }

        void Texture2D::Upload(GLenum target_type, const unsigned char *color, const TextureFormat &format, const Dimension &dimension)
        {
            // 对于单通道纹理，设置1字节对齐以避免 FreeType 位图读取错误
            if (format.gl_internalformat == GL_RED || format.channels == 1)
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            }
            
            glTexImage2D(target_type, format.level, format.gl_internalformat, dimension.width, dimension.height, format.border, format.gl_internalformat, format.data_type, color);
            
            // 恢复默认的4字节对齐
            if (format.gl_internalformat == GL_RED || format.channels == 1)
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            }
        }

        void Texture2D::Upload(GLenum target_type, const std::string &image_path, TextureFormat &format, Dimension &dimension)
        {
            stbi_set_flip_vertically_on_load(format.flip_vertical);
            
            unsigned char *data = stbi_load(image_path.c_str(), &dimension.width, &dimension.height, &format.channels, 0);

            switch (format.channels)
            {
            case 4:
            {
                format.gl_internalformat = GL_RGBA;
                break;
            }
            case 1:
            {
                format.gl_internalformat = GL_RED;
                break;
            }
            default:
            {
                format.gl_internalformat = GL_RGB;
                break;
            }
            }
            
            Upload(target_type, data, format, dimension);

            stbi_image_free(data);
        }

        Texture2D::Texture2D()
            : Texture(GL_TEXTURE_2D)

            , _dimension()
        {
        }

        Texture2D::Texture2D(GLObjectID gl_id)
            : Texture(gl_id, GL_TEXTURE_2D)

            , _dimension()
        {
        }

        Texture2D::~Texture2D()
        {
        }

        Texture2D *Texture2D::Build(const Dimension& dimension, const glm::vec3 &color)
        {
            std::vector<glm::u8vec3> texture_memory(dimension.height * dimension.width, glm::u8vec3(color.r * 255, color.g * 255, color.b * 255));
            
            _format.gl_internalformat = GL_RGB;
            _format.channels = 3;

            _dimension = dimension;

            Bind();  // 绑定纹理后再上传数据

            glTexImage2D(_gl_type, _format.level, _format.gl_internalformat, dimension.width, dimension.height, _format.border, _format.gl_internalformat, _format.data_type, texture_memory.data());

            glGenerateMipmap(_gl_type);

            return this;
        }

        Texture2D *Texture2D::Build(const Dimension& dimension,  const glm::vec4 &color)
        {
            std::vector<glm::u8vec4> texture_memory(dimension.height * dimension.width, glm::u8vec4(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

            _format.gl_internalformat = GL_RGBA;
            _format.channels = 4;

            _dimension = dimension;

            Bind();  // 绑定纹理后再上传数据

            glTexImage2D(_gl_type, _format.level, _format.gl_internalformat, dimension.width, dimension.height, _format.border, _format.gl_internalformat, _format.data_type, texture_memory.data());

            glGenerateMipmap(_gl_type);
            
            return this;
        }

        Texture2D *Texture2D::Build(const std::string &image_path)
        {
            Bind();  // 绑定纹理后再上传数据

            Upload(_gl_type, image_path, _format, _dimension);

            glGenerateMipmap(_gl_type);

            return this;
        }

        Texture2D *Texture2D::Build(const unsigned char *color, const TextureFormat& format, const Dimension& dimension)
        {
            _format = format;
            _dimension = dimension;

            Bind();  // 绑定纹理后再上传数据

            Upload(_gl_type, color, format, dimension);

            glGenerateMipmap(_gl_type);

            return this;
        }

        Texture2D *Texture2D::SetDefaultParameters()
        {
            Bind();  // 绑定纹理后再设置参数

            SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
                ->SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
                ->SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                ->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            return this;
        }

        TextureCube::TextureCube()
            : Texture(GL_TEXTURE_CUBE_MAP)
        {
        }

        TextureCube::TextureCube(GLObjectID gl_id)
            : Texture(gl_id, GL_TEXTURE_CUBE_MAP)
        {
        }

        TextureCube::~TextureCube()
        {
        }

        TextureCube *TextureCube::Build(const std::string &images_path)
        {
            struct face_info {
                GLenum type;
                std::string file_name;
            };

            static const std::vector<face_info> faces_info{ 
                face_info{GL_TEXTURE_CUBE_MAP_POSITIVE_X, "/right.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "/left.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "/top.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "/bottom.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "/front.jpg"}, 
                face_info{GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "/back.jpg"}
            };

            TextureFormat format;
            Texture2D::Dimension dimension;
            for (size_t i = 0; i < faces_info.size(); ++i)
            {
                const face_info& face = faces_info[i];

                Texture2D::Upload(face.type, images_path + face.file_name, format, dimension);
            }

            return this;
        }

        TextureCube *TextureCube::SetDefaultParameters()
        {
            SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
                    ->SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
                    ->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
                    ->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
                    ->SetParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            return this;
        }
    }
}

