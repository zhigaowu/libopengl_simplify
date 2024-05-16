
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

        TextureBuffer::Texture& TextureBuffer::Texture::UploadImage(const std::string &image_path
            , GLboolean flip_vertical/* = 0*/
            , GLint level/* = 0*/
            , GLint internalformat/* = GL_RGB*/
            , GLint border/* = 0*/
            , GLenum format/* = GL_RGB*/
            , GLenum data_type/* = GL_UNSIGNED_BYTE*/)
        {
            stbi_set_flip_vertically_on_load(flip_vertical == 0);
            
            int width, height, nrChannels;
            unsigned char *data = stbi_load(image_path.c_str(), &width, &height, &nrChannels, 0);

            (void)nrChannels;

            glTexImage2D(type, level, internalformat, width, height, border, format, data_type, data);
            glGenerateMipmap(type);

            stbi_image_free(data);

            return *this;
        }
    }
}

