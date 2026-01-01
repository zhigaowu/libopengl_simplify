/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_render_buffer.cpp
 *
 *    Description:  render buffer array implementation
 *
 *        Version:  1.0
 *        Created:  2026-01-01
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#include "libglsimplify_render_buffer.h"

namespace gl_simplify {

    namespace core {

        RenderBufferArray::RenderBufferArray(GLsizei buffer_size/* = 1*/)
            : _gl_render_buffers(buffer_size, 0)
        {
            glGenRenderbuffers(buffer_size, _gl_render_buffers.data());
        }

        RenderBufferArray::~RenderBufferArray()
        {
            glDeleteRenderbuffers(static_cast<GLsizei>(_gl_render_buffers.size()), _gl_render_buffers.data());
        }

        RenderBufferArray& RenderBufferArray::Bind(GLsizei buffer_index/* = 0*/)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, _gl_render_buffers[buffer_index]);

            return *this;
        }

        RenderBufferArray& RenderBufferArray::Storage(GLenum internal_format, GLsizei width, GLsizei height)
        {
            glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);

            return *this;
        }

        RenderBufferArray& RenderBufferArray::StorageMultisample(GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height)
        {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internal_format, width, height);

            return *this;
        }

        void RenderBufferArray::Unbind()
        {
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        GLuint RenderBufferArray::GetRenderBufferID(GLsizei buffer_index/* = 0*/) const
        {
            return _gl_render_buffers[buffer_index];
        }
    }
}
