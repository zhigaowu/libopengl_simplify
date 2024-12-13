
#include "libglsimplify_uniform_array.h"

namespace gl_simplify {

    namespace core {

        UniformArray::UniformArray(GLsizei buffer_size/* = 1*/)
            : BufferArray(GL_UNIFORM_BUFFER, buffer_size)
            , _bind_points(buffer_size)
        {
        }

        UniformArray::~UniformArray()
        {
        }

        UniformArray::BindPoint &UniformArray::GetBindPoint(GLsizei buffer_index, GLuint bind_point)
        {
            BindPoint& bindpoint = _bind_points[buffer_index];
            
            if (0 == bindpoint.type)
            {
                bindpoint = BindPoint(_buffer_ids[buffer_index], _buffer_type, bind_point);
            }

            return bindpoint;
        }
    }
}

