
#include "libglsimplify_buffer_array.h"

namespace gl_simplify {

    namespace core {

        BufferArray::BufferArray(GLenum buffer_type/* = GL_ARRAY_BUFFER*/, GLsizei buffer_size/* = 1*/)
            : _gl_buffer_type(buffer_type)
            , _gl_buffer_arrays(buffer_size, 0)
        {
            glGenBuffers(buffer_size, _gl_buffer_arrays.data());
        }

        BufferArray::~BufferArray()
        {
            glDeleteBuffers(static_cast<GLsizei>(_gl_buffer_arrays.size()), _gl_buffer_arrays.data());
        }
    }
}

