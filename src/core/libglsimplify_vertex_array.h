/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_vertex_array.h
 *
 *    Description:  vertex array logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_VERTEX_ARRAY_H
#define GL_SIMPLIFY_CORE_VERTEX_ARRAY_H

#include "libglsimplify_buffer_array.h"

namespace gl_simplify {

    namespace core {

        class VertexArray : private NonCopyable {
        public:
            explicit VertexArray(GLsizei array_size = 1);
            ~VertexArray();

            VertexArray& Bind(GLsizei array_index = 0)
            {
                glBindVertexArray(_gl_vertex_arrays[array_index]);

                return *this;
            }

            void Unbind()
            {
                glBindVertexArray(0);
            }
        
        private:
            std::vector<GLuint> _gl_vertex_arrays;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_VERTEX_ARRAY_H
