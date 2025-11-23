/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_plane.h
 *
 *    Description:  plane in the scene
 *
 *        Version:  1.0
 *        Created:  2025-11-22 18:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_BASIC_PLANE_H
#define GL_SIMPLIFY_ENTITY_BASIC_PLANE_H

#include "entity/libglsimplify_base_entity.h"

namespace gl_simplify {

    namespace entity::basic {

        class Plane : public BaseEntity {
        public:
        static const VertexDataBuffer& dafaultVertextDataBuffer();
        static const IndexBuffer& defaultIndexBuffer();

        public:
            Plane();
            ~Plane();

            void Render() override;
        };

        using PlanePtr = std::shared_ptr<Plane>;
    }
}

#define CreatePlane() CreateDefaultEntity(gl_simplify::entity::basic::Plane)

#endif // GL_SIMPLIFY_ENTITY_PLANE_H
