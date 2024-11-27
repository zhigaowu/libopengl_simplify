
#include "libglsimplify_cone.h"

#include "entity/libglsimplify_camera.h"

namespace gl_simplify {

    namespace entity {

        static constexpr GLsizei STRIDE_STEP = 8; // Positions(3) Normals(3) Texture Coords(2)

        Cone::Cone(GLint segments, const glm::vec3& position)
            : Entity(position)

            , _vbo()
            , _ebo(GL_ELEMENT_ARRAY_BUFFER)
            , _vao()

            , _theta(0.0f)

            , _vertices()
            , _indices()
        {
            SetSegments(segments);
        }

        Cone::~Cone()
        {
        }

        void Cone::SetSegments(GLint segments)
        {
            if (segments < 3)
            {
                segments = 3;
            }

            _theta = (std::numbers::pi * 2) / segments;

            GLint point_number = segments + 2;
            GLint triangle_number = segments << 1;

            _vertices.resize(point_number * STRIDE_STEP, 0.0f);
            _indices.resize(triangle_number * 3, 0u);
        }

        bool Cone::Update(GLchar *, GLsizei)
        {
            // point 0
            GLfloat* point_data = _vertices.data();
            point_data[1] = 1.0f; // y
            point_data[6] = 0.5f; // u
            point_data[7] = 0.5f; // v
            point_data += STRIDE_STEP;

            // point 1
            point_data[1] = -1.0f; // y
            point_data[6] = 0.5f; // u
            point_data[7] = 0.5f; // v
            point_data += STRIDE_STEP;

            // point 2
            point_data[0] = -1.0f; // x
            point_data[1] = -1.0f; // y
            point_data[6] = 0.0f; // u
            point_data[7] = 0.5f; // v
            point_data += STRIDE_STEP;

            GLfloat theta = _theta;

            GLint point_bottom_index = 3;

            GLuint* indice_data = _indices.data();

            GLfloat* point_end = _vertices.data() + _vertices.size();
            while (point_data < point_end)
            {
                GLfloat x = std::cos(theta + std::numbers::pi);
                GLfloat z = std::sin(theta);

                GLfloat u = 0.5f * (1.0f - std::cos(theta));
                GLfloat v = 0.5f * (1.0f - std::sin(theta));

                // ------------- make up vertice data ------------
                // bottom point
                point_data[0] = x; // x
                point_data[1] = -1.0; // y
                point_data[2] = z; // z
                point_data[6] = u; // u
                point_data[7] = v; // v
                point_data += STRIDE_STEP;

                theta += _theta;
                
                // ------------- make up indice data ------------
                // bottom triangle
                indice_data[0] = 1;
                indice_data[1] = point_bottom_index;
                indice_data[2] = point_bottom_index - 1;
                indice_data += 3;

                // side triangle
                indice_data[0] = 0;
                indice_data[1] = point_bottom_index - 1;
                indice_data[2] = point_bottom_index;
                indice_data += 3;

                point_bottom_index += 1;
            }

            point_bottom_index -= 1;
                
            // ------------- make up indice data ------------
            // bottom triangle
            indice_data[0] = 1;
            indice_data[1] = 2;
            indice_data[2] = point_bottom_index;
            indice_data += 3;

            // side triangle
            indice_data[0] = 0;
            indice_data[1] = point_bottom_index;
            indice_data[2] = 2;
            indice_data += 3;

            // upload data and set data format
            _vao.Bind();

            _vbo.Bind();
            _vbo.Upload(sizeof(GLfloat) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
            _vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, STRIDE_STEP * sizeof(float), (void*)0);
            _vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, STRIDE_STEP * sizeof(float), (void*)(6 * sizeof(float)));
            _vbo.Unbind();

            _ebo.Bind();
            _ebo.Upload(sizeof(GLuint) * _indices.size(), _indices.data(), GL_STATIC_DRAW);

            _vao.Unbind();

            return true;
        }

        void Cone::Draw()
        {
            // draw point
            _vao.Bind();

            glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

            _vao.Unbind();
        }
    }
}

