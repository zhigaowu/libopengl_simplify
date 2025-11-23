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

namespace gl_simplify {

    namespace core {

        class BufferArray : private NonCopyable {
        public:
            explicit BufferArray(GLenum buffer_type = GL_ARRAY_BUFFER, GLsizei buffer_size = 1);
            virtual ~BufferArray();

            BufferArray& Bind(GLsizei buffer_index = 0)
            {
                glBindBuffer(_gl_buffer_type, _gl_buffer_arrays[buffer_index]);

                return *this;
            }

            BufferArray& Upload(GLsizeiptr size, const void *data, GLenum usage)
            {
                glBufferData(_gl_buffer_type, size, data, usage);

                return *this;
            }

            BufferArray& Upload(GLsizeiptr offset, GLsizeiptr size, const void *data, GLenum usage)
            {
                glBufferSubData(_gl_buffer_type, offset, size, data);

                return *this;
            }

            BufferArray& SetAttribute(GLuint attribute_index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
            {
                glVertexAttribPointer(attribute_index, size, type, normalized, stride, offset);
                glEnableVertexAttribArray(attribute_index);

                return *this;
            }

            BufferArray& SetAttributeDivisor(GLuint attribute_index, GLuint divisor)
            {
                glVertexAttribDivisor(attribute_index, divisor);

                return *this;
            }
            
            void Unbind()
            {
                glBindBuffer(_gl_buffer_type, 0);  
            }
        
        protected:
            GLenum _gl_buffer_type;
            GLObjectIDs _gl_buffer_arrays;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_BUFFER_ARRAY_H
