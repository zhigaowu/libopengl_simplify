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
            glm::vec4 _ambient;
            glm::vec4 _diffuse;
            glm::vec4 _specular;

        protected:
            GLfloat _shininess;

        protected:
            void generateDefaultTexture();

        public:
            explicit Material(GLfloat shininess = 32.0f);
            explicit Material(const glm::vec4& ambient, GLfloat shininess = 32.0f);
            Material(const glm::vec4& ambient, const glm::vec4& diffuse, GLfloat shininess = 32.0f);
            Material(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, GLfloat shininess = 32.0f);
            explicit Material(const std::string& path, GLuint texture_unit = GL_TEXTURE0);
            ~Material();

            void SetTexture(const std::string& path);
            void BindTexture();
            void UnbindTexture();

            void SetAmbient(const glm::vec4& ambient);
            const glm::vec4& GetAmbient();

            void SetDiffuse(const glm::vec4& diffuse);
            const glm::vec4& GetDiffuse();

            void SetSpecular(const glm::vec4& specular);
            const glm::vec4& GetSpecular();

            void SetShininess(GLfloat shininess);
            GLfloat GetShininess();

            void Copy(Material* other);
        };

        using SharedMaterial = std::shared_ptr<Material>;
    }
}

#endif // GL_SIMPLIFY_MATERIAL_MATERIAL_H
