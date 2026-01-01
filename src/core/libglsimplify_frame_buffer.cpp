/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_frame_buffer.cpp
 *
 *    Description:  frame buffer array implementation
 *
 *        Version:  1.0
 *        Created:  2026-01-01
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#include "libglsimplify_frame_buffer.h"

namespace gl_simplify {

    namespace core {

        FrameBufferArray::FrameBufferArray(GLsizei buffer_size/* = 1*/)
            : _gl_frame_buffers(buffer_size, 0)
        {
            glGenFramebuffers(buffer_size, _gl_frame_buffers.data());
        }

        FrameBufferArray::~FrameBufferArray()
        {
            glDeleteFramebuffers(static_cast<GLsizei>(_gl_frame_buffers.size()), _gl_frame_buffers.data());
        }

        FrameBufferArray& FrameBufferArray::Bind(GLsizei buffer_index/* = 0*/, GLenum target/* = GL_FRAMEBUFFER*/)
        {
            glBindFramebuffer(target, _gl_frame_buffers[buffer_index]);

            return *this;
        }

        FrameBufferArray& FrameBufferArray::AttachTexture2D(GLenum attachment, GLuint texture_id, GLenum target/* = GL_FRAMEBUFFER*/, GLint level/* = 0*/)
        {
            glFramebufferTexture2D(target, attachment, GL_TEXTURE_2D, texture_id, level);

            return *this;
        }

        FrameBufferArray& FrameBufferArray::AttachRenderBuffer(GLenum attachment, GLuint renderbuffer_id, GLenum target/* = GL_FRAMEBUFFER*/)
        {
            glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, renderbuffer_id);

            return *this;
        }

        FrameBufferArray& FrameBufferArray::AttachTextureCubemap(GLenum attachment, GLuint texture_id, GLenum cubemap_face, GLenum target/* = GL_FRAMEBUFFER*/, GLint level/* = 0*/)
        {
            glFramebufferTexture2D(target, attachment, cubemap_face, texture_id, level);

            return *this;
        }

        bool FrameBufferArray::CheckStatus(GLenum target/* = GL_FRAMEBUFFER*/) const
        {
            return glCheckFramebufferStatus(target) == GL_FRAMEBUFFER_COMPLETE;
        }

        GLenum FrameBufferArray::GetStatus(GLenum target/* = GL_FRAMEBUFFER*/) const
        {
            return glCheckFramebufferStatus(target);
        }

        void FrameBufferArray::Unbind(GLenum target/* = GL_FRAMEBUFFER*/)
        {
            glBindFramebuffer(target, 0);
        }

        GLuint FrameBufferArray::GetFrameBufferID(GLsizei buffer_index/* = 0*/) const
        {
            return _gl_frame_buffers[buffer_index];
        }
    }
}
