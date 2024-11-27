
#include "libglsimplify_camera.h"

namespace gl_simplify {

    namespace entity {

        namespace {

            ViewState::ViewState(Camera& camera)
                : _camera(camera)

                , _target()
                
                , _front()
            {
            }

            ViewState::~ViewState()
            {
            }

            FreeViewState::FreeViewState(Camera& camera)
                : ViewState(camera)

                , _yaw(-90.0f), _pitch(0.0f)
            {
            }

            FreeViewState::~FreeViewState()
            {
            }

            void FreeViewState::updateView()
            {
                // keep view in the front
                _target = _camera._position + _front;
            }

            void FreeViewState::Look(const glm::vec3& vec)
            {
                _front = glm::normalize(vec);

                updateView();
            }

            void FreeViewState::Move(const glm::vec3& step)
            {
                glm::vec3 right = step.x * glm::normalize(glm::cross(_camera._up, _front));
                glm::vec3 up = step.y * _camera._up;
                glm::vec3 top_right_direction = (right + up);

                _camera.Translate(_camera._move_sensitive * top_right_direction);

                updateView();
            }

            void FreeViewState::Rotate(const glm::vec3& step)
            {
                _yaw += step.y * _camera._rotate_sensitive;

                _pitch += step.z * _camera._rotate_sensitive;

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

                updateView();
            }

            void FreeViewState::Forward()
            {
                _camera.Translate(_camera._move_sensitive * _front);

                updateView();
            }

            void FreeViewState::Backward()
            {
                _camera.Translate(-1.0f * _camera._move_sensitive * _front);

                updateView();
            }
            
            void FreeViewState::Left()
            {
                _camera.Translate(_camera._move_sensitive * glm::normalize(glm::cross(_camera._up, _front)));

                updateView();
            }
            
            void FreeViewState::Right()
            {
                _camera.Translate(_camera._move_sensitive * glm::normalize(glm::cross(_front, _camera._up)));

                updateView();
            }

            FocusViewState::FocusViewState(Camera& camera)
                : ViewState(camera)
            {
            }

            FocusViewState::~FocusViewState()
            {
            }

            void FocusViewState::updateView()
            {
                // keep view on the target
                _front = glm::normalize(_target - _camera._position);

                glm::vec3 right = glm::normalize(glm::cross(_camera._up, _front));

                _camera._up = glm::normalize(glm::cross(_front, right));
            }

            void FocusViewState::Look(const glm::vec3& target)
            {
                _target = target;

                updateView();
            }

            void FocusViewState::Move(const glm::vec3& step)
            {
                glm::vec3 right = step.x * glm::normalize(glm::cross(_camera._up, _front));
                glm::vec3 up = step.y * _camera._up;
                glm::vec3 top_right_direction = (right + up);

                _camera.Translate(_camera._move_sensitive * top_right_direction);

                updateView();
            }

            void FocusViewState::Rotate(const glm::vec3& step)
            {
                ;
            }

            void FocusViewState::Forward()
            {
                _camera.Translate(_camera._move_sensitive * _front);
            }

            void FocusViewState::Backward()
            {
                _camera.Translate(-1.0f * _camera._move_sensitive * _front);
            }
            
            void FocusViewState::Left()
            {
                // get rotation matrix
                glm::mat4 rotation_around_y = glm::rotate(glm::mat4(1.0f), _camera._rotate_sensitive, glm::vec3(0.0, 1.0, 0.0));

                // get camera local position in target coordinate system
                glm::vec4 camera_position_to_target = rotation_around_y * glm::vec4(_camera._position - _target, 1.0f);

                // change local position back to world position
                glm::vec3 camera_position_to_world = _target + glm::vec3(camera_position_to_target);

                // move
                _camera.Translate(camera_position_to_world - _camera._position);

                updateView();
            }
            
            void FocusViewState::Right()
            {
                // get rotation matrix
                glm::mat4 rotation_around_y = glm::rotate(glm::mat4(1.0f), -_camera._rotate_sensitive, glm::vec3(0.0, 1.0, 0.0));

                // get camera local position in target coordinate system
                glm::vec4 camera_position_to_target = rotation_around_y * glm::vec4(_camera._position - _target, 1.0f);

                // change local position back to world position
                glm::vec3 camera_position_to_world = _target + glm::vec3(camera_position_to_target);

                // move
                _camera.Translate(camera_position_to_world - _camera._position);

                updateView();
            }
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

            , _move_sensitive(0.03f)
            , _rotate_sensitive(0.1f)
            
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

        bool Camera::Update(GLchar *error, GLsizei error_length)
        {
            return true;
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

        void Camera::Move(const glm::vec3& step)
        {
            _view_state->Move(step);
        }

        void Camera::Rotate(const glm::vec3& step)
        {
            _view_state->Rotate(step);
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

        glm::mat4 Camera::GetView() const
        {
            return glm::lookAt( _position, _view_state->GetTarget(), _up);
        }
    }
}

