/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_default_camera.h
 *
 *    Description:  default camera logic
 *
 *        Version:  1.0
 *        Created:  2025-11-22 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CAMERA_DEFAULT_CAMERA_H
#define GL_SIMPLIFY_CAMERA_DEFAULT_CAMERA_H

#include "libglsimplify_base_camera.h"

namespace gl_simplify {

    namespace camera {

        class DefaultCamera : public BaseCamera {
        public:
            explicit DefaultCamera(GLfloat aspect, GLfloat fovy = glm::radians(45.0f), GLfloat near = 0.1f, GLfloat far = 100.0f, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
            ~DefaultCamera();

            void LookAt(const glm::vec3& target) override;

            void LookFront(const glm::vec3& front) override;
            
            void Forward(const glm::vec3& step) override;
            void Backward(const glm::vec3& step) override;

            void Left(const glm::vec3& step) override;
            void Right(const glm::vec3& step) override;
            
            void Up(const glm::vec3& step) override;
            void Down(const glm::vec3& step) override;

            void Rotate(GLfloat angle) override;
            void Rotate(const glm::vec3& axis, GLfloat angle) override;
        };

        using BasicCameraPtr = std::shared_ptr<DefaultCamera>;
    }
}

#define CreateDefaultCamera(...) CreateWithParameter(gl_simplify::camera::DefaultCamera, __VA_ARGS__)

#endif // GL_SIMPLIFY_CAMERA_DEFAULT_CAMERA_H
