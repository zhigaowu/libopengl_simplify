
#include "libglsimplify_camera.h"

#include <cmath>

namespace gl_simplify {

    namespace entity {

        namespace {
            ViewState::ViewState(Camera& camera)
                : _camera(camera)
                
                , _target()
                , _front()

                , _yaw(-90.0f), _pitch(0.0f)
            {
            }

            ViewState::~ViewState()
            {
            }

            FreeViewState::FreeViewState(Camera& camera)
                : ViewState(camera)
            {
            }

            FreeViewState::~FreeViewState()
            {
            }

            void FreeViewState::Look(const glm::vec3& vec)
            {
                _front = glm::normalize(vec);
                _target = _camera._position + _front;
            }

            void FreeViewState::Rotate(GLfloat yaw_adjusted, GLfloat pitch_adjusted)
            {
                _yaw += yaw_adjusted;

                _pitch += pitch_adjusted;

                if (_pitch > 89.0f)
                {
                    _pitch = 89.0f;
                }
                if (_pitch < -89.0f)
                {
                    _pitch = -89.0f;
                }

                glm::vec3 direction(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
                    sin(glm::radians(_pitch)),
                    sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));

                _front = glm::normalize(direction);
                _target = _camera._position + _front;
            }

            void FreeViewState::Forward()
            {
                _camera.Move(_camera._move_sensitive * _front);
            }

            void FreeViewState::Backward()
            {
                _camera.Move(-1.0f * _camera._move_sensitive * _front);
            }
            
            void FreeViewState::Left()
            {
                glm::vec3 move_steps = _camera._move_sensitive * glm::normalize(glm::cross(_camera._up, _front));

                // update _target
                _target = (_camera._position + move_steps) + _front;
            }
            
            void FreeViewState::Right()
            {
                glm::vec3 move_steps = _camera._move_sensitive * glm::normalize(glm::cross(_front, _camera._up));

                // update _target
                _target = (_camera._position + move_steps) + _front;
            }
        }

        FocusViewState::FocusViewState(Camera& camera)
                : ViewState(camera)
            {
            }

        FocusViewState::~FocusViewState()
        {
        }

        void FocusViewState::Look(const glm::vec3& target)
        {
            _target = target;

            _front = glm::normalize(_target - _camera._position);
        }

        void FocusViewState::Rotate(GLfloat yaw_adjusted, GLfloat pitch_adjusted)
        {
            _yaw += yaw_adjusted;

            _pitch += pitch_adjusted;

            if (_pitch > 89.0f)
            {
                _pitch = 89.0f;
            }
            if (_pitch < -89.0f)
            {
                _pitch = -89.0f;
            }

            glm::vec3 direction(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
                sin(glm::radians(_pitch)),
                sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));

            _front = glm::normalize(direction);
            _target = _camera._position + _front;
        }

        void FocusViewState::Forward()
        {
            _camera.Move(_camera._move_sensitive * _front);
        }

        void FocusViewState::Backward()
        {
            _camera.Move(-1.0f * _camera._move_sensitive * _front);
        }
        
        void FocusViewState::Left()
        {
            glm::vec3 move_steps = _camera._move_sensitive * glm::normalize(glm::cross(_camera._up, _front));

            // update _front
            _front = glm::normalize(_target - (_camera._position + move_steps));
        }
        
        void FocusViewState::Right()
        {
            glm::vec3 move_steps = _camera._move_sensitive * glm::normalize(glm::cross(_front, _camera._up));

            // update _front
            _front = glm::normalize(_target - (_camera._position + move_steps));
        }

        void Camera::fixPerspectiveFovy()
        {
            if (_projection_component.x < _min_fovy_radian)
            {
                _projection_component.x = _min_fovy_radian;
            }
            if (_projection_component.x > _max_fovy_radian)
            {
                _projection_component.x = _max_fovy_radian;
            }
        }

        Camera::Camera(GLfloat aspect, 
            GLfloat fovy/* = glm::radians(45.0f)*/, 
            GLfloat near/* = 0.1f*/, 
            GLfloat far/* = 100.0f*/, 
            const glm::vec3& up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/)
            : Entity()

            , _up(up)

            , _move_sensitive(0.05f)
            , _rotate_sensitive(0.05f)
            
            , _min_fovy_radian(glm::radians(1.0f))
            , _max_fovy_radian(glm::radians(60.0f))
            , _projection_component(fovy, aspect, near, far)
            , _projection(glm::perspective(fovy, aspect, near, far))

            , _free_view_state(*this)
            , _focus_view_state(*this)
            , _view_state(&_free_view_state)
        {
        }

        Camera::~Camera()
        {
        }

        bool Camera::Initialize(GLchar *error, GLsizei error_length)
        {
            return true;
        }

        void Camera::Render(Camera* camera)
        {
        }

        void Camera::LookAt(const glm::vec3 &target)
        {
            _view_state = &_focus_view_state;
            _view_state->Look(target);
        }

        void Camera::LookFront(const glm::vec3 &front)
        {
            _view_state = &_free_view_state;
            _view_state->Look(front);
        }

        void Camera::Forward()
        {
            _view_state->Forward();
        }

        void Camera::Backward()
        {
            _view_state->Backward();
        }

        void Camera::Left()
        {
            _view_state->Left();
        }

        void Camera::Right()
        {
            _view_state->Right();
        }

        void Camera::Rotate(GLfloat yaw_adjusted, GLfloat pitch_adjusted)
        {
            _view_state = &_free_view_state;
            _view_state->Rotate(yaw_adjusted, pitch_adjusted);
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

        glm::mat4 Camera::GetView()
        {
            return glm::lookAt( _position, _view_state->GetTarget(), _up);
        }
    }
}

