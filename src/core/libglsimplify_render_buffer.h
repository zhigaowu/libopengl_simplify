/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_render_buffer.h
 *
 *    Description:  render buffer array logic
 *
 *        Version:  1.0
 *        Created:  2026-01-01
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_RENDER_BUFFER_H
#define GL_SIMPLIFY_CORE_RENDER_BUFFER_H

#include "libglsimplify_types.h"

namespace gl_simplify {

    namespace core {

        class RenderBufferArray : private NonCopyable {
        public:
            explicit RenderBufferArray(GLsizei buffer_size = 1);
            virtual ~RenderBufferArray();

            RenderBufferArray& Bind(GLsizei buffer_index = 0);
            RenderBufferArray& Storage(GLenum internal_format, GLsizei width, GLsizei height);
            RenderBufferArray& StorageMultisample(GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height);
            
            void Unbind();
            GLuint GetRenderBufferID(GLsizei buffer_index = 0) const;

        protected:
            GLObjectIDs _gl_render_buffers;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_RENDER_BUFFER_H
