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
            core::TextureBuffer _texture_buffer;

        protected:
            GLfloat _shininess;

        public:
            explicit Material(GLfloat shininess = 32.0f);
            Material(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, GLfloat shininess = 32.0f);
            Material(const std::string& diffuse_map_path, const std::string& specular_map_path, GLfloat shininess = 32.0f);
            ~Material();

            void SetDiffuseMap(const std::string& path);
            void SetSpecularMap(const std::string& path);
            void BindTexture();
            void UnbindTexture();

            void SetDiffuse(const glm::vec4& diffuse);
            GLint GetDiffuse();

            void SetSpecular(const glm::vec4& specular);
            GLint GetSpecular();
            
            void SetShininess(GLfloat shininess);
            GLfloat GetShininess();
        };

        using MaterialPtr = std::shared_ptr<Material>;
        using SharedMaterial = std::shared_ptr<Material>;
    }
}

#endif // GL_SIMPLIFY_MATERIAL_MATERIAL_H
