/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_uniform_array.h
 *
 *    Description:  uniform array logic
 *
 *        Version:  1.0
 *        Created:  2024-12-13 16:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_UNIFORM_ARRAY_H
#define GL_SIMPLIFY_CORE_UNIFORM_ARRAY_H

#include "libglsimplify_buffer_array.h"

namespace gl_simplify {

    namespace core {

        class UniformArray : public BufferArray {
        public:
            class BindPoint {
            public:
                GLuint type;
                GLuint id;
                GLuint point;

            public:
                BindPoint()
                    : type(0)
                    , id(0)
                    , point(0)
                {
                }
                explicit BindPoint(GLuint in_id, GLuint in_type = GL_UNIFORM_BUFFER, GLuint in_point = 0)
                    : type(in_type)
                    , id(in_id)
                    , point(in_point)
                {
                }

                ~BindPoint()
                {}

                BindPoint(BindPoint&& ref)
                    : type(ref.type)
                    , id(ref.id)
                    , point(ref.point)
                {
                }

                BindPoint& operator=(BindPoint&& ref)
                {
                    type = ref.type;
                    id = ref.id;
                    point = ref.point;

                    return *this;
                }

                BindPoint(const BindPoint& ref)
                    : type(ref.type)
                    , id(ref.id)
                    , point(ref.point)
                {
                }

                BindPoint& operator=(const BindPoint& ref)
                {
                    type = ref.type;
                    id = ref.id;
                    point = ref.point;

                    return *this;
                }

                void Bind()
                {
                    glBindBufferBase(type, point, id);
                }

                void Bind(GLintptr offset, GLsizeiptr size)
                {
                    glBindBufferRange(type, point, id, offset, size);
                }
            };

        public:
            explicit UniformArray(GLsizei buffer_size = 1);
            ~UniformArray();

            BindPoint& GetBindPoint(GLsizei buffer_index = 0, GLuint bind_point = 0);

        private:
            using BindPoints = std::vector<BindPoint>;
            BindPoints _bind_points;
        };
    }
}

#endif // GL_SIMPLIFY_CORE_UNIFORM_ARRAY_H
