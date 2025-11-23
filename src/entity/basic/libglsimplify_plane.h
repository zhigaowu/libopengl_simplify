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
        private:
            GLuint _index_count;

        public:
            explicit Plane(GLfloat width = 2.0f, GLfloat height = 2.0f, GLint width_segments = 1, GLint height_segments = 1, GLboolean double_sided = GL_FALSE);
            ~Plane();

            void Reset(GLfloat width = 2.0f, GLfloat height = 2.0f, GLint width_segments = 1, GLint height_segments = 1, GLboolean double_sided = GL_FALSE);

            void Render() override;
        };

        using PlanePtr = std::shared_ptr<Plane>;
    }
}

#define CreatePlane() CreateDefault(gl_simplify::entity::basic::Plane)
#define CreatePlaneOf(...) CreateWithParameter(gl_simplify::entity::basic::Plane, __VA_ARGS__)

#endif // GL_SIMPLIFY_ENTITY_PLANE_H
