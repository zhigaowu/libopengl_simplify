
#include "libglsimplify_vertex_array.h"

namespace gl_simplify {

    namespace core {

        VertexArray::VertexArray(GLsizei buffer_size/* = 1*/)
            : _buffer_ids(buffer_size, 0)
        {
            glGenVertexArrays(buffer_size, _buffer_ids.data());
        }

        VertexArray::~VertexArray()
        {
            glDeleteVertexArrays(static_cast<GLsizei>(_buffer_ids.size()), _buffer_ids.data());
        }

        VertexArray& VertexArray::Bind(const VertexArrayConfigurer& vertexarray_configurer, GLsizei buffer_index/* = 0*/)
        {
            glBindVertexArray(_buffer_ids[buffer_index]);

            vertexarray_configurer(*this);

            return *this;
        }
    }
}

