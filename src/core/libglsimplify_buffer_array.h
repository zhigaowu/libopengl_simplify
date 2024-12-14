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

#include <vector>

namespace gl_simplify {

    namespace core {

        class BufferArray : private NonCopyable {
        public:
            explicit BufferArray(GLenum buffer_type = GL_ARRAY_BUFFER, GLsizei buffer_size = 1);
            virtual ~BufferArray();

            BufferArray& Bind(GLsizei buffer_index = 0)
            {
                glBindBuffer(_buffer_type, _buffer_ids[buffer_index]);

                return *this;
            }

            void Upload(GLsizeiptr size, const void *data, GLenum usage)
            {
                glBufferData(_buffer_type, size, data, usage);
            }

            void Upload(GLsizeiptr offset, GLsizeiptr size, const void *data, GLenum usage)
            {
                glBufferSubData(_buffer_type, offset, size, data);
            }

            void SetAttribute(GLuint attribute_index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
            {
                glVertexAttribPointer(attribute_index, size, type, normalized, stride, offset);
                glEnableVertexAttribArray(attribute_index);
            }

            void SetAttributeDivisor(GLuint attribute_index, GLuint divisor)
            {
                glVertexAttribDivisor(attribute_index, divisor);
            }
            
            void Unbind()
            {
                glBindBuffer(_buffer_type, 0);  
            }
        
        protected:
            GLenum _buffer_type;
            std::vector<GLuint> _buffer_ids;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_BUFFER_ARRAY_H
