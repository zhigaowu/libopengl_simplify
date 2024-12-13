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
            GLint _segments;
            
        public:
            explicit Cylinder(GLint segments = 32, const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Cylinder();

            void SetSegments(GLint segments);

            void Create() override;
        };

        using CylinderPtr = std::shared_ptr<Cylinder>;
    }
}

#define CreateCylinder() CreateDefaultEntity(gl_simplify::entity::Cylinder)

#endif // GL_SIMPLIFY_ENTITY_CYLINDER_H
