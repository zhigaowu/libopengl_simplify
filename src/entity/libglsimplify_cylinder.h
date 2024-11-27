/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_cylinder.h
 *
 *    Description:  cylinder in the scene
 *                  cylinder has three parties: top circle, bottom circle and side rectangles
 *                                                     
 *                  points and indicies                
 *                                                     
 *                          * 8                        
 *                    **          **                   
 *               **                     **             
 *         2 *              0                * 6       
 *           *   **                     **   *         
 *           *        **          **         *         
 *           *            4 *                *         
 *           *              *                *         
 *           *              *                *         
 *           *              *                *         
 *           *              *                *         
 *           *              *                *         
 *           *              - 9              *         
 *           *        --    *     --         *         
 *           *   --         *           --   *         
 *         3 *              1                * 7       
 *               **         *           **             
 *                    **    *     **                   
 *                        5 *                          
 *                                                     
 *        Version:  1.0
 *        Created:  2024-11-25 16:56:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_CYLINDER_H
#define GL_SIMPLIFY_ENTITY_CYLINDER_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        class Cylinder : public Entity {
            gl_simplify::core::BufferArray _vbo;
            gl_simplify::core::BufferArray _ebo;
            gl_simplify::core::VertexArray _vao;

            GLfloat _theta;

            std::vector<GLfloat> _vertices;
            std::vector<GLuint> _indices;

        public:
            explicit Cylinder(GLint segments = 32, const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Cylinder();

            void SetSegments(GLint segments);

            bool Update(GLchar* error, GLsizei error_length) override;
            void Draw() override;
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_CYLINDER_H
