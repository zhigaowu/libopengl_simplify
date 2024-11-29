/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_plane.h
 *
 *    Description:  plane in the scene
 *
 *        Version:  1.0
 *        Created:  2024-11-22 18:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_PLANE_H
#define GL_SIMPLIFY_ENTITY_PLANE_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        class Plane : public Entity {
        public:
            explicit Plane(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Plane();

            void Create() override;
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_PLANE_H
