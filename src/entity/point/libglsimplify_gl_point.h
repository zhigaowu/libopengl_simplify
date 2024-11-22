/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_gl_point.h
 *
 *    Description:  opengl point in the scene
 *
 *        Version:  1.0
 *        Created:  2024-11-19 14:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_POINT_H
#define GL_SIMPLIFY_ENTITY_POINT_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        namespace point {

            class GLPoint : public Entity {
                gl_simplify::core::BufferArray _vbo;
                gl_simplify::core::BufferArray _ebo;
                gl_simplify::core::VertexArray _vao;

            public:
                explicit GLPoint(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
                ~GLPoint();

                void SetSize(GLfloat size);

                bool Initialize(GLchar* error, GLsizei error_length) override;
                void Render(Camera* camera) override;
            };
        }
    }
}

#endif // GL_SIMPLIFY_ENTITY_POINT_H
