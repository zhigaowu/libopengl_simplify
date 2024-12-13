
#include "libglsimplify_buffer_array.h"

namespace gl_simplify {

    namespace core {

        BufferArray::BufferArray(GLenum buffer_type/* = GL_ARRAY_BUFFER*/, GLsizei buffer_size/* = 1*/)
            : _buffer_type(buffer_type)
            , _buffer_ids(buffer_size, 0)
        {
            glGenBuffers(buffer_size, _buffer_ids.data());
        }

        BufferArray::~BufferArray()
        {
            glDeleteBuffers(static_cast<GLsizei>(_buffer_ids.size()), _buffer_ids.data());
        }
    }
}

