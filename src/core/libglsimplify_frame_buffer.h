/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_frame_buffer.h
 *
 *    Description:  frame buffer array logic
 *
 *        Version:  1.0
 *        Created:  2026-01-01
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_FRAME_BUFFER_H
#define GL_SIMPLIFY_CORE_FRAME_BUFFER_H

#include "libglsimplify_types.h"

namespace gl_simplify {

    namespace core {

        class FrameBufferArray : private NonCopyable {
        public:
            explicit FrameBufferArray(GLsizei buffer_size = 1);
            virtual ~FrameBufferArray();

            FrameBufferArray& Bind(GLsizei buffer_index = 0, GLenum target = GL_FRAMEBUFFER);
            FrameBufferArray& AttachTexture2D(GLenum attachment, GLuint texture_id, GLenum target = GL_FRAMEBUFFER, GLint level = 0);
            FrameBufferArray& AttachRenderBuffer(GLenum attachment, GLuint renderbuffer_id, GLenum target = GL_FRAMEBUFFER);
            FrameBufferArray& AttachTextureCubemap(GLenum attachment, GLuint texture_id, GLenum cubemap_face, GLenum target = GL_FRAMEBUFFER, GLint level = 0);
            
            bool CheckStatus(GLenum target = GL_FRAMEBUFFER) const;
            GLenum GetStatus(GLenum target = GL_FRAMEBUFFER) const;
            
            void Unbind(GLenum target = GL_FRAMEBUFFER);
            GLuint GetFrameBufferID(GLsizei buffer_index = 0) const;

        protected:
            GLObjectIDs _gl_frame_buffers;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_FRAME_BUFFER_H
