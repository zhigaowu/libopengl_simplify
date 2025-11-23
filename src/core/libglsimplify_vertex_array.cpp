
#include "libglsimplify_vertex_array.h"

namespace gl_simplify {

    namespace core {

        VertexArray::VertexArray(GLsizei array_size/* = 1*/)
            : _gl_vertex_arrays(array_size, 0)
        {
            glGenVertexArrays(array_size, _gl_vertex_arrays.data());
        }

        VertexArray::~VertexArray()
        {
            glDeleteVertexArrays(static_cast<GLsizei>(_gl_vertex_arrays.size()), _gl_vertex_arrays.data());
        }
    }
}

