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

        class VertexArray {
        public:
            using VertexArrayConfigurer = std::function<void(VertexArray&)>;

        public:
            explicit VertexArray(GLsizei buffer_size = 1);
            ~VertexArray();

            VertexArray& Bind(GLsizei buffer_index = 0)
            {
                glBindVertexArray(_buffer_ids[buffer_index]);

                return *this;
            }

            VertexArray& Bind(const VertexArrayConfigurer& vertexarray_configurer, GLsizei buffer_index = 0);

            void Unbind()
            {
                glBindVertexArray(0);
            }

        public:
            VertexArray(VertexArray&&) = delete;
            VertexArray& operator=(VertexArray&&) = delete;

            VertexArray(const VertexArray&) = delete;
            VertexArray& operator=(const VertexArray&) = delete;
        
        private:
            std::vector<GLuint> _buffer_ids;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_VERTEX_ARRAY_H
