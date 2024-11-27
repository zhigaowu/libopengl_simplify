/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_cone.h
 *
 *    Description:  cone in the scene
 *                  cone has two parties: bottom circle and side triangles
 *                                                     
 *                  points and indicies                
 *                                                     
 *                       0  *                          
 *                        *   *                        
 *                      *   *   *                      
 *                     *    *    *                     
 *                    *     *     *                    
 *                  *       *      *                   
 *                 *        *       *                  
 *                *         *        *                 
 *               *          *         *                
 *              *           *          *               
 *             *            *           *              
 *            *             *            *             
 *           *              - 5           *            
 *          *         --    *     --       *           
 *      2  *     --         *           --  *          
 *           *              1                *  4      
 *               *          *            *             
 *                    *     *      *                   
 *                       3  *                          
 *                                                     
 *        Version:  1.0
 *        Created:  2024-11-27 09:47:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_CONE_H
#define GL_SIMPLIFY_ENTITY_CONE_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        class Cone : public Entity {
            gl_simplify::core::BufferArray _vbo;
            gl_simplify::core::BufferArray _ebo;
            gl_simplify::core::VertexArray _vao;

            GLfloat _theta;

            std::vector<GLfloat> _vertices;
            std::vector<GLuint> _indices;

        public:
            explicit Cone(GLint segments = 32, const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Cone();

            void SetSegments(GLint segments);

            bool Update(GLchar* error, GLsizei error_length) override;
            void Draw() override;
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_CONE_H
