/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_line.h
 *
 *    Description:  line in the scene
 *                  line has three parties: begin circle, end circle and side rectangles
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
 *        Created:  2025-04-30 20:30:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_LINE_H
#define GL_SIMPLIFY_ENTITY_LINE_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        class Line : public Entity {
            GLint _segments;
            
        public:
            explicit Line(GLint segments = 32, const glm::vec3& position = glm::vec3(0.0, 0.0, 0.0));
            ~Line();

            void SetSegments(GLint segments);

            void Create() override;
        };

        using LinePtr = std::shared_ptr<Line>;
    }
}

#define CreateLine() CreateDefaultEntity(gl_simplify::entity::Line)

#endif // GL_SIMPLIFY_ENTITY_LINE_H
