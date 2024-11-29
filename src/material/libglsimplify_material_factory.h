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
            static void Initialize();
            static void Shutdown();
            
            static MaterialFactory* Instance();

            SharedMaterial Create(GLuint texture_unit = GL_TEXTURE0);
        };
    }
}

#endif // GL_SIMPLIFY_MATERIAL_MATERIAL_FACTORY_H
