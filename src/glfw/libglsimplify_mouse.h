/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_mouse.h
 *
 *    Description:  mouse information
 *
 *        Version:  1.0
 *        Created:  2024-11-21 10:00:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_GLFW_MOUSE_H
#define GL_SIMPLIFY_GLFW_MOUSE_H

namespace gl_simplify {

    namespace glfw {

        struct Mouse {
            bool left_button_down;
            bool middle_button_down;
            bool right_button_down;

            float x;
            float y;
            
            Mouse()
                : left_button_down(false)
                , middle_button_down(false)
                , right_button_down(false)

                , x(0.0f)
                , y(0.0f)
            {
            }
        };
    }
}

#endif // GL_SIMPLIFY_GLFW_MOUSE_H
