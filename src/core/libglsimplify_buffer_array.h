/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_buffer_array.h
 *
 *    Description:  buffer array logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_BUFFER_ARRAY_H
#define GL_SIMPLIFY_CORE_BUFFER_ARRAY_H

#include "libglsimplify_types.h"

#include <functional>
#include <vector>

namespace gl_simplify {

    namespace core {

        class BufferArray : private NonCopyable {
        public:
            using BufferArrayConfigurer = std::function<void(BufferArray&)>;

        public:
            explicit BufferArray(GLenum buffer_type = GL_ARRAY_BUFFER, GLsizei buffer_size = 1);
            ~BufferArray();

            BufferArray& Bind(GLsizei buffer_index = 0)
            {
                glBindBuffer(_buffer_type, _buffer_ids[buffer_index]);

                return *this;
            }

            BufferArray& Bind(const BufferArrayConfigurer& buffer_array_configurer, GLsizei buffer_index = 0);

            void Upload(GLsizeiptr size, const void *data, GLenum usage)
            {
                glBufferData(_buffer_type, size, data, usage);
            }

            void SetAttribute(GLuint attribute_index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
            {
                glVertexAttribPointer(attribute_index, size, type, normalized, stride, offset);
                glEnableVertexAttribArray(attribute_index);
            }
            
            void Unbind()
            {
                glBindBuffer(_buffer_type, 0);  
            }
        
        private:
            GLenum _buffer_type;
            std::vector<GLuint> _buffer_ids;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_BUFFER_ARRAY_H