/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_sphere.h
 *
 *    Description:  sphere in the scene
 *                  sphere has three parameters: radius, latitude, longitude
 *        Version:  1.0
 *        Created:  2025-06-09 20:40:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_SPHERE_H
#define GL_SIMPLIFY_ENTITY_SPHERE_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        class Sphere : public Entity {
            GLuint _radius;
            GLuint _latitude_segments;
            GLuint _longitude_segments;
            
        public:
            explicit Sphere(GLuint radius = 1, const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            Sphere(GLuint radius, GLuint latitude_segments, GLuint longitude_segments, const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Sphere();

            void SetRadius(GLuint radius);

            void SetLatitudeSegments(GLuint latitude_segments);
            void SetLongitudeSegments(GLuint longitude_segments);

            void Create() override;
        };

        using SpherePtr = std::shared_ptr<Sphere>;
    }
}

#define CreateSphere() CreateDefaultEntity(gl_simplify::entity::Sphere)

#endif // GL_SIMPLIFY_ENTITY_SPHERE_H
