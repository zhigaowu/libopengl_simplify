
#include "libglsimplify_texture_buffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace gl_simplify {

    namespace core {

        TextureBuffer::TextureBuffer(GLsizei texture_count/* = 1*/)
            : _textures(texture_count)
            , _texture_ids(texture_count)

        {
            glGenTextures(static_cast<GLsizei>(_texture_ids.size()), _texture_ids.data());
        }

        TextureBuffer::~TextureBuffer()
        {
            glDeleteTextures(static_cast<GLsizei>(_texture_ids.size()), _texture_ids.data());
        }

        TextureBuffer::Texture& TextureBuffer::GetTexture(GLint index/* = 0*/, GLenum texture_type/* = GL_TEXTURE_2D*/)
        {
            if (0 == _textures[index].type)
            {
                _textures[index] = Texture(_texture_ids[index], texture_type);
            }

            return _textures[index];
        }

        TextureBuffer::Texture &TextureBuffer::Texture::UploadColor(const glm::vec4 &color, GLint level, GLint border)
        {
            width = 64;
            height = 64;

            std::vector<GLubyte> texture_memory(height * (width * 3), 0);

            GLubyte R = color.r * 255;
            GLubyte G = color.g * 255;
            GLubyte B = color.b * 255;

            GLubyte* rgb = texture_memory.data();
            for (int r = 0; r < height; ++r)
            {
                for (int c = 0; c < width; ++c)
                {
                    rgb[0] = R;
                    rgb[1] = G;
                    rgb[2] = B;

                    rgb += 3;
                }
            }
            
            glTexImage2D(type, level, GL_RGB, width, height, border, GL_RGB, GL_UNSIGNED_BYTE, texture_memory.data());
            glGenerateMipmap(type);

            return *this;
        }

        TextureBuffer::Texture &TextureBuffer::Texture::UploadImage(const std::string &image_path, GLboolean flip_vertical /* = 0*/
                                                                    ,
                                                                    GLint level /* = 0*/
                                                                    ,
                                                                    GLint border /* = 0*/
                                                                    ,
                                                                    GLenum data_type /* = GL_UNSIGNED_BYTE*/)
        {
            stbi_set_flip_vertically_on_load(flip_vertical == 0);
            
            int nrChannels;
            unsigned char *data = stbi_load(image_path.c_str(), &width, &height, &nrChannels, 0);

            switch (nrChannels)
            {
            case 4:
            {
                glTexImage2D(type, level, GL_RGBA, width, height, border, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            }
            case 1:
            {
                glTexImage2D(type, level, GL_RED, width, height, border, GL_RED, GL_UNSIGNED_BYTE, data);
                break;
            }
            default:
                glTexImage2D(type, level, GL_RGB, width, height, border, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            }

            glGenerateMipmap(type);

            stbi_image_free(data);

            return *this;
        }
    }
}

