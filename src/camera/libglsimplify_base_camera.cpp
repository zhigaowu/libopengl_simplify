
#include "libglsimplify_base_camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl_simplify {

    namespace camera {

        BaseCamera::BaseCamera(GLfloat aspect, 
            GLfloat fovy/* = glm::radians(45.0f)*/, 
            GLfloat near/* = 0.1f*/, 
            GLfloat far/* = 100.0f*/, 
            const glm::vec3& up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/)

            : core::NonCopyable()

            , _aspect(aspect)
            , _fovy(fovy)
            , _near(near)
            , _far(far)

            , _position(glm::vec3(0.0f, 0.0f, 0.0f))
            , _up(glm::normalize(up))

            , _front(glm::vec3(0.0f, 0.0f, -1.0f))
            , _target(glm::vec3(0.0f, 0.0f, 0.0f))

            , _entity(nullptr)

            , _keep_aspect(false)

            , _fovy_min(glm::radians(1.0f))
            , _fovy_max(glm::radians(120.0f))
        {
        }

        BaseCamera::~BaseCamera()
        {
        }

        void BaseCamera::SetAspect(GLfloat aspect)
        {
            if (!_keep_aspect)
            {
                _aspect = aspect;
            }
        }

        void BaseCamera::SetFovy(GLfloat fovy)
        {
            _fovy = glm::clamp(fovy, _fovy_min, _fovy_max);
        }

        void BaseCamera::setFovyLimits(GLfloat fovy_min, GLfloat fovy_max)
        {
            _fovy_min = fovy_min;
            _fovy_max = fovy_max;
        }

        void BaseCamera::SetNear(GLfloat near)
        {
            _near = near;
        }

        void BaseCamera::SetFar(GLfloat far)
        {
            _far = far;
        }

        void BaseCamera::SetPosition(const glm::vec3 &position)
        {
            _position = position;
        }

        void BaseCamera::LookAt(const glm::vec3 &target)
        {
            _target = target;
            // 更新 front 向量，使相机朝向目标
            _front = glm::normalize(target - _position);
        }

        void BaseCamera::LookFront(const glm::vec3 &front)
        {
            _front = glm::normalize(front);
        }

        glm::mat4 BaseCamera::GetView() const
        {
            return glm::lookAt(_position, _position + _front, _up);
        }

        glm::mat4 BaseCamera::GetProjection() const
        {
            return glm::perspective(_fovy, _aspect, _near, _far);
        }
    }
}

