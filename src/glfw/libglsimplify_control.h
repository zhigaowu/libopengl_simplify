/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_control.h
 *
 *    Description:  control logic and information
 *
 *        Version:  1.0
 *        Created:  2025-11-23 12:00:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_GLFW_CONTROL_H
#define GL_SIMPLIFY_GLFW_CONTROL_H

#include "core/libglsimplify_types.h"

namespace gl_simplify {

    namespace glfw {

        struct Mouse {
            bool left_button_down;
            bool middle_button_down;
            bool right_button_down;

            GLfloat x;
            GLfloat y;
            
            Mouse()
                : left_button_down(false)
                , middle_button_down(false)
                , right_button_down(false)

                , x(0.0f)
                , y(0.0f)
            {
            }
        };

        struct CameraControl {
            GLfloat movement_speed;
            GLfloat rotation_sensitivity;

            GLfloat last_frame_time;
            GLfloat delta_time;

            GLfloat pan_speed;

            GLfloat fov_sensitivity;
            
            CameraControl()
                : movement_speed(4.0f)
                , rotation_sensitivity(0.1f)
                , last_frame_time(0.0f)
                , delta_time(0.0f)

                , pan_speed(0.005f)
                
                , fov_sensitivity(0.1f)
            {
            }

            GLfloat GetDeltaMovement() const
            {
                return movement_speed * delta_time;
            }

            void UpdateFrameTime(GLfloat current_time)
            {
                delta_time = current_time - last_frame_time;
                last_frame_time = current_time;
            }
        };
    }
}

#endif // GL_SIMPLIFY_GLFW_CONTROL_H
