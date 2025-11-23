/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_sphere.h
 *
 *    Description:  sphere in the scene
 *
 *        Version:  1.0
 *        Created:  2025-11-23 18:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_BASIC_SPHERE_H
#define GL_SIMPLIFY_ENTITY_BASIC_SPHERE_H

#include "entity/libglsimplify_base_entity.h"

namespace gl_simplify {

    namespace entity::basic {

        class Sphere : public BaseEntity {
        public:
            explicit Sphere(GLfloat radius = 1.0f, GLint stacks = 10, GLint sectors = 10);
            ~Sphere();

            void Reset(GLfloat radius = 1.0f, GLint stacks = 10, GLint sectors = 10);

            void Render() override;
        };

        using SpherePtr = std::shared_ptr<Sphere>;
    }
}

#define CreateSphere() CreateDefault(gl_simplify::entity::basic::Sphere)
#define CreateSphereOf(...) CreateWithParameter(gl_simplify::entity::basic::Sphere, __VA_ARGS__)

#endif // GL_SIMPLIFY_ENTITY_BASIC_SPHERE_H

