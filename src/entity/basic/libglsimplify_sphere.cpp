
#include "libglsimplify_sphere.h"

#include <cmath>

namespace gl_simplify {

    namespace entity::basic {

        Sphere::Sphere(GLfloat radius, GLint stacks, GLint sectors)
            : BaseEntity()
        {
            Reset(radius, stacks, sectors);
        }

        Sphere::~Sphere()
        {
        }

        void Sphere::Reset(GLfloat radius, GLint stacks, GLint sectors)
        {
            VertexDataBuffer vertex_data_buffer;
            
            // stacks: 纬度方向的分割数（堆叠层数）
            // sectors: 经度方向的分割数（扇区数）
            if (stacks < 2) stacks = 2;
            if (sectors < 3) sectors = 3;
            
            // 生成球体顶点
            for (int i = 0; i <= stacks; ++i)
            {
                float stackAngle = std::numbers::pi / 2.0f - i * std::numbers::pi / stacks; // 从 π/2 到 -π/2
                float xy = radius * std::cos(stackAngle);                                   // r * cos(θ)
                float y = radius * std::sin(stackAngle);                                    // r * sin(θ)

                for (int j = 0; j <= sectors; ++j)
                {
                    float sectorAngle = j * 2.0f * std::numbers::pi / sectors; // 从 0 到 2π

                    // 计算顶点位置
                    float x = xy * std::cos(sectorAngle);
                    float z = xy * std::sin(sectorAngle);

                    // 法线（对于球体，法线就是归一化的位置向量）
                    glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));

                    // 纹理坐标
                    float u = (float)j / sectors;
                    float v = (float)i / stacks;

                    vertex_data_buffer.push_back({
                        glm::vec3(x, y, z), // position
                        normal,             // normal
                        glm::vec2(u, v)     // texcoord
                    });
                }
            }

            IndexBuffer index_buffer;
            // 生成索引以形成三角形
            for (int i = 0; i < stacks; ++i)
            {
                int k1 = i * (sectors + 1); // 当前层的起始索引
                int k2 = k1 + sectors + 1;  // 下一层的起始索引

                for (int j = 0; j < sectors; ++j, ++k1, ++k2)
                {
                    if (i != 0)
                    {
                        // 上三角形
                        index_buffer.push_back(k1);
                        index_buffer.push_back(k2);
                        index_buffer.push_back(k1 + 1);
                    }

                    if (i != (stacks - 1))
                    {
                        // 下三角形
                        index_buffer.push_back(k1 + 1);
                        index_buffer.push_back(k2);
                        index_buffer.push_back(k2 + 1);
                    }
                }
            }

            _index_count = static_cast<GLuint>(index_buffer.size());

            // 设置顶点和索引数据
            createDefaultArrays();

            configureDefaultVertexAttributes(vertex_data_buffer, index_buffer);
        }

        void Sphere::Render()
        {
            _vao->Bind();

            glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, 0);
            
            _vao->Unbind();
        }

    }
}

