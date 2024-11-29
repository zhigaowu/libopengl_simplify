
#include "libglsimplify_cone.h"

namespace gl_simplify {

    namespace entity {

        Cone::Cone(GLint segments, const glm::vec3& position)
            : Entity(position)

            , _segments(segments)
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

            _segments = segments;
        }

        void Cone::Create()
        {
            // allocate data buffer
            const GLfloat theta_step = (std::numbers::pi * 2) / _segments;

            GLint triangle_number = _segments << 1;
            GLint point_number = triangle_number * 3;

            _vertices.resize(point_number * VERTEX_STRIDE_WITH_NORMAL_UV, 0.0f);
            _indices.resize(point_number, 0u);

            // prepare the top and bottom circle information
            const glm::vec3 top_circle_center_position(0.0f, 1.0f, 0.0f);
            const glm::vec2 top_circle_center_uv(0.5f, 0.5f);

            const glm::vec3 bottom_circle_center_position(0.0f, -1.0f, 0.0f);
            const glm::vec2 bottom_circle_center_uv(0.5f, 0.5f);
            const glm::vec3 bottom_circle_plane_normal(0.0f, -1.0f, 0.0f);

            // make up the vertex and indice data
            GLfloat theta = 0.0f;

            GLfloat* point_data = _vertices.data();
            GLuint* indice_data = _indices.data();

            GLuint point_index = 0;

            // -- vertex data is orgnized in counter-clockwise order
            for (GLint segment = 0; segment < _segments; ++segment)
            {
                /*
                 * ----------- bottom triangle ------------
                */
                // next bottom point
                GLfloat x = std::cos(theta + std::numbers::pi);
                GLfloat z = std::sin(theta);
                glm::vec3 next_bottom_point_position(x, bottom_circle_center_position.y, z);

                GLfloat u = 0.5f * (1.0f - std::cos(theta));
                GLfloat v = 0.5f * (1.0f - std::sin(theta));
                glm::vec2 next_bottom_point_uv(u, v);

                // first bottom point
                theta += theta_step;

                x = std::cos(theta + std::numbers::pi);
                z = std::sin(theta);
                glm::vec3 first_bottom_point_position(x, bottom_circle_center_position.y, z);

                u = 0.5f * (1.0f - std::cos(theta));
                v = 0.5f * (1.0f - std::sin(theta));
                glm::vec2 first_bottom_point_uv(u, v);

                // bottom center point
                point_data[0] = bottom_circle_center_position.x; // x
                point_data[1] = bottom_circle_center_position.y; // y
                point_data[2] = bottom_circle_center_position.z; // z
                point_data[3] = bottom_circle_plane_normal.x; // normal_x
                point_data[4] = bottom_circle_plane_normal.y; // normal_y
                point_data[5] = bottom_circle_plane_normal.z; // normal_z
                point_data[6] = bottom_circle_center_uv.x; // u
                point_data[7] = bottom_circle_center_uv.y; // v
                point_data += VERTEX_STRIDE_WITH_NORMAL_UV;

                *indice_data = point_index++;
                ++indice_data;

                // first bottom point
                point_data[0] = first_bottom_point_position.x; // x
                point_data[1] = first_bottom_point_position.y; // y
                point_data[2] = first_bottom_point_position.z; // z
                point_data[3] = bottom_circle_plane_normal.x; // normal_x
                point_data[4] = bottom_circle_plane_normal.y; // normal_y
                point_data[5] = bottom_circle_plane_normal.z; // normal_z
                point_data[6] = first_bottom_point_uv.x; // u
                point_data[7] = first_bottom_point_uv.y; // v
                point_data += VERTEX_STRIDE_WITH_NORMAL_UV;

                *indice_data = point_index++;
                ++indice_data;

                // next bottom point
                point_data[0] = next_bottom_point_position.x; // x
                point_data[1] = next_bottom_point_position.y; // y
                point_data[2] = next_bottom_point_position.z; // z
                point_data[3] = bottom_circle_plane_normal.x; // normal_x
                point_data[4] = bottom_circle_plane_normal.y; // normal_y
                point_data[5] = bottom_circle_plane_normal.z; // normal_z
                point_data[6] = next_bottom_point_uv.x; // u
                point_data[7] = next_bottom_point_uv.y; // v
                point_data += VERTEX_STRIDE_WITH_NORMAL_UV;

                *indice_data = point_index++;
                ++indice_data;

                /*
                 * ----------- side triangle ------------
                */
                glm::vec3 top_center_point_to_next_bottom_point_direction = next_bottom_point_position - top_circle_center_position;
                glm::vec3 top_center_point_to_first_bottom_point_direction = first_bottom_point_position - top_circle_center_position;
                glm::vec3 side_triangle_plane_normal = glm::normalize(glm::cross(top_center_point_to_next_bottom_point_direction, top_center_point_to_first_bottom_point_direction));

                // top center point
                point_data[0] = top_circle_center_position.x; // x
                point_data[1] = top_circle_center_position.y; // y
                point_data[2] = top_circle_center_position.z; // z
                point_data[3] = side_triangle_plane_normal.x; // normal_x
                point_data[4] = side_triangle_plane_normal.y; // normal_y
                point_data[5] = side_triangle_plane_normal.z; // normal_z
                point_data[6] = top_circle_center_uv.x; // u
                point_data[7] = top_circle_center_uv.y; // v
                point_data += VERTEX_STRIDE_WITH_NORMAL_UV;

                *indice_data = point_index++;
                ++indice_data;

                // next bottom point
                point_data[0] = next_bottom_point_position.x; // x
                point_data[1] = next_bottom_point_position.y; // y
                point_data[2] = next_bottom_point_position.z; // z
                point_data[3] = side_triangle_plane_normal.x; // normal_x
                point_data[4] = side_triangle_plane_normal.y; // normal_y
                point_data[5] = side_triangle_plane_normal.z; // normal_z
                point_data[6] = next_bottom_point_uv.x; // u
                point_data[7] = next_bottom_point_uv.y; // v
                point_data += VERTEX_STRIDE_WITH_NORMAL_UV;

                *indice_data = point_index++;
                ++indice_data;

                // first bottom point
                point_data[0] = first_bottom_point_position.x; // x
                point_data[1] = first_bottom_point_position.y; // y
                point_data[2] = first_bottom_point_position.z; // z
                point_data[3] = side_triangle_plane_normal.x; // normal_x
                point_data[4] = side_triangle_plane_normal.y; // normal_y
                point_data[5] = side_triangle_plane_normal.z; // normal_z
                point_data[6] = first_bottom_point_uv.x; // u
                point_data[7] = first_bottom_point_uv.y; // v
                point_data += VERTEX_STRIDE_WITH_NORMAL_UV;

                *indice_data = point_index++;
                ++indice_data;
            }

            createDefaultArrays();

            bindDefaultVertexLayout();
        }
    }
}

