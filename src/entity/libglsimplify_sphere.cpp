
#include "libglsimplify_sphere.h"

namespace gl_simplify {

    namespace entity {
        Sphere::Sphere(GLuint radius, const glm::vec3 &position)
            : Entity(position)

            , _radius(radius)
            , _latitude_segments(16)
            , _longitude_segments(16)
        {
        }

        Sphere::Sphere(GLuint radius, GLuint latitude_segments, GLuint longitude_segments, const glm::vec3& position)
            : Entity(position)

            , _radius(radius)
            , _latitude_segments(latitude_segments)
            , _longitude_segments(longitude_segments)
        {
        }

        Sphere::~Sphere()
        {
        }

        void Sphere::SetRadius(GLuint radius)
        {
            _radius = radius;
        }

        void Sphere::SetLatitudeSegments(GLuint latitude_segments)
        {
            _latitude_segments = latitude_segments;
        }

        void Sphere::SetLongitudeSegments(GLuint longitude_segments)
        {
            _longitude_segments = longitude_segments;
        }

        void Sphere::Create()
        {
            GLuint point_number = (_latitude_segments + 1) * (_longitude_segments + 1);

            _vertices.resize(point_number * VERTEX_STRIDE_WITH_NORMAL_UV, 0.0f);
            _indices.resize(point_number * 6, 0u);

            GLfloat* vertices = _vertices.data();
            GLuint* indices = _indices.data();

            for (GLuint lat = 0; lat <= _latitude_segments; ++lat) 
            {
                float theta = lat * std::numbers::pi / _latitude_segments;
                float sinTheta = sin(theta);
                float cosTheta = cos(theta);
                
                for (GLuint lon = 0; lon <= _longitude_segments; ++lon) 
                {
                    float phi = lon * 2 * std::numbers::pi / _longitude_segments;
                    float sinPhi = sin(phi);
                    float cosPhi = cos(phi);
                    
                    // 顶点位置
                    float x = _radius * sinTheta * cosPhi;
                    float y = _radius * cosTheta;
                    float z = _radius * sinTheta * sinPhi;
                    
                    // 法线 (与位置相同，因为球体中心在原点)
                    float nx = x;
                    float ny = y;
                    float nz = z;
                    
                    // 添加到顶点数组
                    vertices[0] = x;
                    vertices[1] = y;
                    vertices[2] = z;
                    vertices[3] = nx;
                    vertices[4] = ny;
                    vertices[5] = nz;

                    vertices += VERTEX_STRIDE_WITH_NORMAL_UV;

                    // 设置索引
                    GLuint first = (lat * (_longitude_segments + 1)) + lon;
                    GLuint second = first + _longitude_segments + 1;
                    
                    indices[0] = first;
                    indices[1] = second;
                    indices[2] = first + 1;
                    
                    indices[3] = second;
                    indices[4] = second + 1;
                    indices[5] = first + 1;

                    indices += 6;
                }
            }

            createDefaultArrays();

            bindDefaultVertexLayout();
        }
    }
}

