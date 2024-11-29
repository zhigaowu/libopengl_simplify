/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_material.h
 *
 *    Description:  material logic
 *
 *        Version:  1.0
 *        Created:  2024-11-27 15:18:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_MATERIAL_MATERIAL_H
#define GL_SIMPLIFY_MATERIAL_MATERIAL_H

#include "core/libglsimplify_texture_buffer.h"

#include <memory>

namespace gl_simplify {

    namespace material {

        class Material : public std::enable_shared_from_this<Material> {
        protected:
            GLuint _texture_unit;
            core::TextureBuffer _texture_buffer;

        protected:
            glm::vec4 _color;

        protected:
            GLfloat _specular_strength;
            GLuint _specular_shininess;

        public:
            explicit Material(GLuint texture_unit = GL_TEXTURE0);
            ~Material();

            void SetTexture(const std::string& path);
            void BindTexture();
            void UnbindTexture();

            void SetColor(const glm::vec4& color);
            const glm::vec4& GetColor();

            void SetSpecularStrength(GLfloat specular_strength);
            GLfloat GetSpecularStrength();

            void SetSpecularShininess(GLuint specular_shininess);
            GLuint GetSpecularShininess();
        };

        using SharedMaterial = std::shared_ptr<Material>;
    }
}

#endif // GL_SIMPLIFY_MATERIAL_MATERIAL_H
