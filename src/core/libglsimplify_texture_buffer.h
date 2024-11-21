/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_texture_buffer.h
 *
 *    Description:  texture logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_TEXTURE_BUFFER_H
#define GL_SIMPLIFY_CORE_TEXTURE_BUFFER_H

#include "libglsimplify_types.h"

#include <string>
#include <vector>

namespace gl_simplify {

    namespace core {

        class TextureBuffer : private NonCopyable {
        public:
            class Texture {
            public:
                GLuint id;
                GLenum type;

            public:
                explicit Texture(GLuint texture_id = 0, GLenum texture_type = 0)
                    : id(texture_id)
                    , type(texture_type)
                {
                }

                ~Texture()
                {}

                Texture(Texture&& ref)
                    : id(ref.id)
                    , type(ref.type)
                {
                }

                Texture& operator=(Texture&& ref)
                {
                    id = ref.id;
                    type = ref.type;

                    return *this;
                }

                Texture(const Texture& ref)
                    : id(ref.id)
                    , type(ref.type)
                {
                }

                Texture& operator=(const Texture& ref)
                {
                    id = ref.id;
                    type = ref.type;

                    return *this;
                }

                Texture& Bind(GLuint texture_unit_id = GL_TEXTURE0)
                {
                    glActiveTexture(texture_unit_id);
                    glBindTexture(type, id);

                    return *this;
                }

                Texture& SetParameter(GLenum pname, GLint pvalue)
                {
                    glTexParameteri(type, pname, pvalue);

                    return *this;
                }

                Texture& UploadImage(const std::string &image_path, GLboolean flip_vertical = 0, GLint level = 0, GLint internalformat = GL_RGB, GLint border = 0, GLenum format = GL_RGB, GLenum data_type = GL_UNSIGNED_BYTE);

                void Unbind()
                {
                    glBindTexture(type, 0);
                }
            };
            
        public:
            explicit TextureBuffer(GLsizei texture_count = 1);
            ~TextureBuffer();

            Texture& GetTexture(GLint index = 0, GLenum texture_type = GL_TEXTURE_2D);
        
        private:
            std::vector<Texture> _textures;
            std::vector<GLuint> _texture_ids;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_TEXTURE_BUFFER_H
