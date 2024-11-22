/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_cube.h
 *
 *    Description:  opengl cube in the scene
 *
 *        Version:  1.0
 *        Created:  2024-11-22 14:56:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_CUBE_H
#define GL_SIMPLIFY_ENTITY_CUBE_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        class Cube : public Entity {
            gl_simplify::core::BufferArray _vbo;
            gl_simplify::core::BufferArray _ebo;
            gl_simplify::core::VertexArray _vao;

        public:
            explicit Cube(const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Cube();

            bool Initialize(GLchar* error, GLsizei error_length) override;
            void Render(Camera* camera) override;
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_CUBE_H
