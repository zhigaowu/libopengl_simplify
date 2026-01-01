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

namespace gl_simplify {

    namespace core {

        // 纹理基础类
        class Texture : private NonCopyable {
        public:
            struct TextureFormat {
                GLint channels = 4;
                GLint gl_internalformat = GL_RGBA;

                GLboolean flip_vertical = 0; 
                GLint level = 0; 
                GLint border = 0; 
                GLenum data_type = GL_UNSIGNED_BYTE;
            };

        public:
            explicit Texture(GLenum texture_type);
            Texture(GLObjectID gl_id, GLenum texture_type);

            virtual ~Texture();

            Texture* SetUnit(GLuint texture_unit = GL_TEXTURE0);
            Texture* ActiveUnit();

            GLuint GetUnit() const { return _gl_unit; }
            GLuint GetUnitIndex() const { return _gl_unit - GL_TEXTURE0; }

            Texture* Bind();

            void Unbind();

            Texture* SetParameter(GLenum pname, GLint pvalue);

            void SetFormatFlipVertical(GLboolean flip_vertical) { _format.flip_vertical = flip_vertical; }
            void setFormatLevel(GLint level) { _format.level = level; }
            void setFormatBorder(GLint border) { _format.border = border; }
            void setFormatDataType(GLenum data_type) { _format.data_type = data_type; }

            const TextureFormat& GetFormat() const { return _format; }

        private:
            bool _self_generated;

        private:
            GLuint _gl_unit;
        
        protected:
            GLObjectID _gl_id;
            GLenum _gl_type;

        protected:
            TextureFormat _format;
        };
        using TexturePtr = std::shared_ptr<Texture>;

        // 2D 纹理类
        class Texture2D : public Texture {
        public:
            struct Dimension
            {
                GLint width = 0;
                GLint height = 0;
            };
            
        public:
            static void Upload(GLenum target_type, const unsigned char* color, const TextureFormat& format, const Dimension& dimension);
            static void Upload(GLenum target_type, const std::string &image_path, TextureFormat& format, Dimension& dimension);

        public:
            explicit Texture2D();
            explicit Texture2D(GLObjectID gl_id);
            ~Texture2D();

            Texture2D* Build(const Dimension& dimension, const glm::vec3& color);
            
            Texture2D* Build(const Dimension& dimension, const glm::vec4& color);

            Texture2D* Build(const std::string &image_path);

            Texture2D* Build(const unsigned char* color, const TextureFormat& format, const Dimension& dimension);

            Texture2D* SetDefaultParameters();

            const Dimension& GetDimension() const { return _dimension; }

        private:
            Dimension _dimension;
        };
        using Texture2DPtr = std::shared_ptr<Texture2D>;
        
#define CreateTexture2D() CreateDefault(gl_simplify::core::Texture2D)
#define CreateTexture2DFrom(objectID) CreateWithParameter(gl_simplify::core::Texture2D, objectID)

        // Cube 立方体纹理类
        class TextureCube : public Texture {
        public:
            explicit TextureCube();
            explicit TextureCube(GLObjectID gl_id);
            ~TextureCube();

            TextureCube* Build(const std::string &images_path);

            TextureCube* SetDefaultParameters();
        };
        using TextureCubePtr = std::shared_ptr<TextureCube>;
        
#define CreateTextureCube() CreateDefault(gl_simplify::core::TextureCube)
#define CreateTextureCubeFrom(objectID) CreateWithParameter(gl_simplify::core::TextureCube, objectID)
            
        // 纹理缓冲区模板类【用于管理多个纹理对象】
        template<typename TextureObject>
        class TextureBuffer : private NonCopyable {
            using TextureObjectPtr = std::shared_ptr<TextureObject>;
            using TextureObjects = std::vector<TextureObjectPtr>;

        public:
            explicit TextureBuffer(GLsizei texture_count = 1)
                : NonCopyable()

                , _texture_objects(texture_count)
                , _gl_textures(texture_count)

            {
                glGenTextures(static_cast<GLsizei>(_gl_textures.size()), _gl_textures.data());

                for (size_t i = 0; i < _gl_textures.size(); ++i)
                {
                    _texture_objects[i] = std::make_shared<TextureObject>(_gl_textures[i]);
                }
                
            }

            ~TextureBuffer()
            {
                glDeleteTextures(static_cast<GLsizei>(_gl_textures.size()), _gl_textures.data());
            }

            TextureObjectPtr GetTexture(GLint index = 0)
            {
                return _texture_objects[index];
            }
        
        private:
            TextureObjects _texture_objects;
            GLObjectIDs _gl_textures;
        };

        using Texture2DBuffer = TextureBuffer<Texture2D>;
        using Texture2DBufferPtr = std::shared_ptr<Texture2DBuffer>;
        
#define CreateTexture2DBuffer() CreateDefault(gl_simplify::core::Texture2DBuffer)
#define CreateTexture2DBufferOf(objectCount) CreateWithParameter(gl_simplify::core::Texture2DBuffer, objectCount)

        using TextureCubeBuffer = TextureBuffer<TextureCube>;
        using TextureCubeBufferPtr = std::shared_ptr<TextureCubeBuffer>;
        
#define CreateTextureCubeBuffer() CreateDefault(gl_simplify::core::TextureCubeBuffer)
#define CreateTextureCubeBufferOf(objectCount) CreateWithParameter(gl_simplify::core::TextureCubeBuffer, objectCount)
    }
}

#endif // GL_SIMPLIFY_CORE_TEXTURE_BUFFER_H
