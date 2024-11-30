/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_material_factory.h
 *
 *    Description:  material factory logic
 *
 *        Version:  1.0
 *        Created:  2024-11-28 09:39:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_MATERIAL_MATERIAL_FACTORY_H
#define GL_SIMPLIFY_MATERIAL_MATERIAL_FACTORY_H

#include "libglsimplify_material.h"

namespace gl_simplify {

    namespace material {

        class MaterialFactory : public core::NonCopyable {
        private:
            explicit MaterialFactory();
            ~MaterialFactory();

        public:
            /*
             * reference:
             * http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
            */
            enum class PredefinedMaterialType {
                Brass = 0,
                Bronze,
                BronzePolished,
                Chrome,
                Copper,
                CopperPolished,
                Gold,
                GoldPolished,
                Tin,
                Silver,
                SilverPolished,
                Emerald,
                Jade,
                Obsidian,
                Perl,
                Ruby,
                Turquoise,
                PlasticBlack,
                PlasticCyan,
                PlasticGreen,
                PlasticRed,
                PlasticWhite,
                PlasticYellow,
                RubberBlack,
                RubberCyan,
                RubberGreen,
                RubberRed,
                RubberWhite,
                RubberYellow
            };

        public:
            static SharedMaterial Create();

            static SharedMaterial Create(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, GLfloat shininess = 32.0f);

            static SharedMaterial Create(const std::string& diffuse_map_path, const std::string& specular_map_path, GLfloat shininess = 32.0f);

            static SharedMaterial GetShared(const PredefinedMaterialType& material_type);
        };
    }
}

#endif // GL_SIMPLIFY_MATERIAL_MATERIAL_FACTORY_H
