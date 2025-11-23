
#include "libglsimplify_plane.h"

namespace gl_simplify
{
    namespace entity::basic
    {
        Plane::Plane(GLfloat width, GLfloat height, GLint width_segments, GLint height_segments, GLboolean double_sided)
            : BaseEntity()
            , _index_count(0)
        {
            Reset(width, height, width_segments, height_segments, double_sided);
        }

        Plane::~Plane()
        {
        }

        void Plane::Reset(GLfloat width, GLfloat height, GLint width_segments, GLint height_segments, GLboolean double_sided)
        {
            VertexDataBuffer vertex_data_buffer;

            // width: 平面宽度（X轴方向）
            // height: 平面高度（Z轴方向）
            // width_segments: 宽度方向的分割数
            // height_segments: 高度方向的分割数
            // double_sided: 是否绘制双面

            GLfloat half_width = width * 0.5f;
            GLfloat half_height = height * 0.5f;

            GLfloat segment_width = width / width_segments;
            GLfloat segment_height = height / height_segments;

            // 生成顶点数据
            // 沿 Z 轴（高度）方向遍历
            for (GLint iz = 0; iz <= height_segments; ++iz)
            {
                GLfloat z = iz * segment_height - half_height;  // 从 -half_height 到 +half_height

                // 沿 X 轴（宽度）方向遍历
                for (GLint ix = 0; ix <= width_segments; ++ix)
                {
                    GLfloat x = ix * segment_width - half_width;  // 从 -half_width 到 +half_width

                    // 顶点位置（Y=0 的水平面）
                    glm::vec3 position(x, 0.0f, z);

                    // 法线（向上）
                    glm::vec3 normal(0.0f, 1.0f, 0.0f);

                    // 纹理坐标
                    GLfloat u = static_cast<GLfloat>(ix) / width_segments;
                    GLfloat v = static_cast<GLfloat>(iz) / height_segments;
                    glm::vec2 texcoord(u, v);

                    vertex_data_buffer.push_back({position, normal, texcoord});
                }
            }

            IndexBuffer index_buffer;
            // 生成索引（每个网格单元生成两个三角形）
            for (GLint iz = 0; iz < height_segments; ++iz)
            {
                for (GLint ix = 0; ix < width_segments; ++ix)
                {
                    // 当前网格单元四个顶点的索引
                    GLuint a = iz * (width_segments + 1) + ix;           // 左上
                    GLuint b = a + 1;                                    // 右上
                    GLuint c = (iz + 1) * (width_segments + 1) + ix;     // 左下
                    GLuint d = c + 1;                                    // 右下

                    // 第一个三角形 (a-c-b)
                    index_buffer.push_back(a);
                    index_buffer.push_back(c);
                    index_buffer.push_back(b);

                    // 第二个三角形 (b-c-d)
                    index_buffer.push_back(b);
                    index_buffer.push_back(c);
                    index_buffer.push_back(d);
                }
            }

            // 如果需要双面绘制，将索引逆序复制一份（绘制另一面）
            if (double_sided)
            {
                GLuint single_side_count = index_buffer.size();
                for (GLuint i = 0; i < single_side_count; i += 3)
                {
                    // 逆序添加三角形索引（改变绕序）
                    index_buffer.push_back(index_buffer[i + 2]);
                    index_buffer.push_back(index_buffer[i + 1]);
                    index_buffer.push_back(index_buffer[i]);
                }
            }

            _index_count = static_cast<GLuint>(index_buffer.size());

            // 设置顶点和索引数据
            createDefaultArrays();

            configureDefaultVertexAttributes(vertex_data_buffer, index_buffer);
        }

        void Plane::Render()
        {
            _vao->Bind();

            glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);

            _vao->Unbind();
        }

    }
}


