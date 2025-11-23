#include "libglsimplify_default_camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl_simplify {

    namespace camera {

        DefaultCamera::DefaultCamera(GLfloat aspect, 
            GLfloat fovy/* = glm::radians(45.0f)*/, 
            GLfloat near/* = 0.1f*/, 
            GLfloat far/* = 100.0f*/, 
            const glm::vec3& up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/)

            : BaseCamera(aspect, fovy, near, far, up)
        {
        }

        DefaultCamera::~DefaultCamera()
        {
        }

        void DefaultCamera::LookAt(const glm::vec3 &target)
        {
            BaseCamera::LookAt(target);
        }

        void DefaultCamera::LookFront(const glm::vec3 &front)
        {
            BaseCamera::LookFront(front);
        }

        void DefaultCamera::Forward(const glm::vec3& step)
        {
            _position += _front * step.z;
        }

        void DefaultCamera::Backward(const glm::vec3& step)
        {
            _position -= _front * step.z;
        }

        void DefaultCamera::Left(const glm::vec3& step)
        {
            glm::vec3 right = glm::normalize(glm::cross(_front, _up));
            _position -= right * step.x;
        }

        void DefaultCamera::Right(const glm::vec3& step)
        {
            glm::vec3 right = glm::normalize(glm::cross(_front, _up));
            _position += right * step.x;
        }

        void DefaultCamera::Up(const glm::vec3 &step)
        {
            _position += _up * step.y;
        }

        void DefaultCamera::Down(const glm::vec3 &step)
        {
            _position -= _up * step.y;
        }

        void DefaultCamera::Rotate(GLfloat angle)
        {
            // 围绕 up 轴旋转 front 向量（水平旋转，即 yaw）
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), _up);
            _front = glm::vec3(rotation * glm::vec4(_front, 0.0f));
            _front = glm::normalize(_front);
        }

        void DefaultCamera::Rotate(const glm::vec3 &axis, GLfloat angle)
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
            _front = glm::vec3(rotation * glm::vec4(_front, 0.0f));
            _front = glm::normalize(_front);
        }
    }
}

