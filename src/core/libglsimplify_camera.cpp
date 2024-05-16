
#include "libglsimplify_camera.h"

#include <cmath>

namespace gl_simplify {

    namespace core {

        Camera::Camera(GLfloat aspect, 
            GLfloat fovy/* = glm::radians(45.0f)*/, 
            GLfloat near/* = 0.1f*/, 
            GLfloat far/* = 100.0f*/, 
            const glm::vec3& up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/)
            : _min_fovy_radian(glm::radians(1.0f))
            , _max_fovy_radian(glm::radians(60.0f))
            , _projection_component(fovy, aspect, near, far)
            , _projection(glm::perspective(fovy, aspect, near, far))

            , _up(up)
            , _location()

            , _look_front_state()
            , _look_at_state()
            , _look_state(&_look_front_state)
        {
        }

        Camera::~Camera()
        {
        }

        Camera::Camera(Camera&& ref)
            : _min_fovy_radian(ref._min_fovy_radian)
            , _max_fovy_radian(ref._max_fovy_radian)
            , _projection_component(ref._projection_component)
            , _projection(ref._projection)

            , _up(ref._up)
            , _location(ref._location)

            , _look_front_state(ref._look_front_state)
            , _look_at_state(ref._look_at_state)
            , _look_state(ref._look_state)
        {
        }

        Camera& Camera::operator=(Camera&& ref)
        {
            _min_fovy_radian = ref._min_fovy_radian;
            _max_fovy_radian = ref._max_fovy_radian;
            
            _projection_component = ref._projection_component;
            _projection = ref._projection;

            _up = ref._up;
            _location = ref._location;

            _look_front_state = ref._look_front_state;
            _look_at_state = ref._look_at_state;
            _look_state = ref._look_state;

            return *this;
        }

        Camera::Camera(const Camera& ref)
            : _min_fovy_radian(ref._min_fovy_radian)
            , _max_fovy_radian(ref._max_fovy_radian)
            , _projection_component(ref._projection_component)
            , _projection(ref._projection)

            , _up(ref._up)
            , _location(ref._location)

            , _look_front_state(ref._look_front_state)
            , _look_at_state(ref._look_at_state)
            , _look_state(ref._look_state)
        {
        }

        Camera& Camera::operator=(const Camera& ref)
        {
            _min_fovy_radian = ref._min_fovy_radian;
            _max_fovy_radian = ref._max_fovy_radian;
            
            _projection_component = ref._projection_component;
            _projection = ref._projection;

            _up = ref._up;
            _location = ref._location;

            _look_front_state = ref._look_front_state;
            _look_at_state = ref._look_at_state;
            _look_state = ref._look_state;

            return *this;
        }

        void Camera::MoveTo(GLfloat x, GLfloat y, GLfloat z)
        {
            _location = glm::vec3(x, y, z);

            _look_state->MoveTo(_location);
        }

        void Camera::MoveTo(const glm::vec3 &location)
        {
            _location = location;
            
            _look_state->MoveTo(_location);
        }

        void Camera::LookFront(GLfloat x, GLfloat y, GLfloat z)
        {
            _look_state = &_look_front_state;
            _look_state->Look(_location, glm::vec3(x, y, z));
        }

        void Camera::LookFront(const glm::vec3 &_front)
        {
            _look_state = &_look_front_state;
            _look_state->Look(_location, _front);
        }

        void Camera::RotateTo(GLfloat yaw, GLfloat pitch)
        {
            _look_state = &_look_front_state;

            _look_state->RotateTo(_location, yaw, pitch);
        }

        void Camera::Rotate(GLfloat yaw_adjusted, GLfloat pitch_adjusted)
        {
            _look_state = &_look_front_state;
            _look_state->Rotate(_location, yaw_adjusted, pitch_adjusted);
        }

        void Camera::LookAt(GLfloat x, GLfloat y, GLfloat z)
        {
            _look_state = &_look_at_state;
            _look_state->Look(_location, glm::vec3(x, y, z));
        }

        void Camera::LookAt(const glm::vec3 &_target)
        {
            _look_state = &_look_at_state;
            _look_state->Look(_location, _target);
        }

        void Camera::SetPerspectiveAspect(GLfloat aspect)
        {
            _projection_component.y = aspect;
            _projection = glm::perspective(_projection_component.x, _projection_component.y, _projection_component.z, _projection_component.w);
        }

        void Camera::SetPerspectiveFovyRange(GLfloat fovy_min, GLfloat fovy_max)
        {
            _min_fovy_radian = fovy_min;
            _max_fovy_radian = fovy_max;
        }

        void Camera::SetPerspectiveFovy(GLfloat fovy)
        {
            _projection_component.x = fovy;

            fixPerspectiveFovy();

            _projection = glm::perspective(_projection_component.x, _projection_component.y, _projection_component.z, _projection_component.w);
        }

        void Camera::AdjustPerspectiveFovyDegree(GLfloat degree_adjusted)
        {
            _projection_component.x += glm::radians(degree_adjusted);

            fixPerspectiveFovy();

            _projection = glm::perspective(_projection_component.x, _projection_component.y, _projection_component.z, _projection_component.w);
        }

        void Camera::AdjustPerspectiveFovyRadian(GLfloat radian_adjusted)
        {
            _projection_component.x += radian_adjusted;

            fixPerspectiveFovy();

            _projection = glm::perspective(_projection_component.x, _projection_component.y, _projection_component.z, _projection_component.w);
        }

        void Camera::SetPerspectiveNear(GLfloat near)
        {
            _projection_component.z = near;
            _projection = glm::perspective(_projection_component.x, _projection_component.y, _projection_component.z, _projection_component.w);
        }

        void Camera::SetPerspectiveFar(GLfloat far)
        {
            _projection_component.w = far;
            _projection = glm::perspective(_projection_component.x, _projection_component.y, _projection_component.z, _projection_component.w);
        }

        void Camera::Forward(GLfloat steps)
        {
            _location += _look_state->Forward(steps);
        }

        void Camera::Backward(GLfloat steps)
        {
            _location += _look_state->Backward(steps);
        }

        void Camera::Left(GLfloat steps)
        {
            _location += _look_state->Left(_location, _up, steps);
        }

        void Camera::Right(GLfloat steps)
        {
            _location += _look_state->Right(_location, _up, steps);
        }
    }
}

