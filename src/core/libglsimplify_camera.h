/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_camera.h
 *
 *    Description:  camera logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_CORE_CAMERA_H
#define GL_SIMPLIFY_CORE_CAMERA_H

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl_simplify {

    namespace core {

        class Camera {
        private:
            GLfloat _min_fovy_radian;
            GLfloat _max_fovy_radian;

            glm::vec4 _projection_component;
            glm::mat4 _projection;

        private:
            glm::vec3 _up;
            glm::vec3 _location;

        private:
            class LookState
            {
                void eularToVector(const glm::vec3& camera_location)
                {
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
                    _target = camera_location + _front;
                }

            protected:
                glm::vec3 _target;

            protected:
                glm::vec3 _front;

            protected:
                GLfloat _yaw;
                GLfloat _pitch;

            public:
                LookState()
                    : _target()

                    , _front()

                    , _yaw(-90.0f), _pitch(0.0f)
                {
                }

                virtual ~LookState()
                {
                }

                LookState(LookState&&) = default;
                LookState& operator=(LookState&&) = default;

                LookState(const LookState&) = default;
                LookState& operator=(const LookState&) = default;

                const glm::vec3& GetTarget() { return _target; }
                const glm::vec3& GetFront() { return _front; }

                virtual void Look(const glm::vec3& camera_location, const glm::vec3& vec) = 0;

                virtual void MoveTo(const glm::vec3& camera_location) = 0;
                virtual glm::vec3 Forward(GLfloat steps) = 0;
                virtual glm::vec3 Backward(GLfloat steps) = 0;
                virtual glm::vec3 Left(const glm::vec3& camera_location, const glm::vec3& camera_up, GLfloat steps) = 0;
                virtual glm::vec3 Right(const glm::vec3& camera_location, const glm::vec3& camera_up, GLfloat steps) = 0;

                void RotateTo(const glm::vec3& camera_location, GLfloat yaw, GLfloat pitch)
                {
                    _yaw = yaw;
                    _pitch = pitch;

                    eularToVector(camera_location);
                }

                void Rotate(const glm::vec3& camera_location, GLfloat yaw_adjusted, GLfloat pitch_adjusted)
                {
                    _yaw += yaw_adjusted;

                    _pitch += pitch_adjusted;

                    eularToVector(camera_location);
                }

            };

            class LookFrontState : public LookState
            {
            public:
                LookFrontState()
                    : LookState()
                {
                }

                ~LookFrontState()
                {
                }

                LookFrontState(LookFrontState&&) = default;
                LookFrontState& operator=(LookFrontState&&) = default;

                LookFrontState(const LookFrontState&) = default;
                LookFrontState& operator=(const LookFrontState&) = default;

                void Look(const glm::vec3& camera_location, const glm::vec3& vec) override
                {
                    _front = glm::normalize(vec);
                    _target = camera_location + _front;
                }

                void MoveTo(const glm::vec3& camera_location) override
                {
                    _target = camera_location + _front;
                }

                glm::vec3 Forward(GLfloat steps) override
                {
                    return steps * _front;
                }

                glm::vec3 Backward(GLfloat steps) override
                {
                    return -1.0f * steps * _front;
                }
                
                glm::vec3 Left(const glm::vec3& camera_location, const glm::vec3& camera_up, GLfloat steps) override
                {
                    glm::vec3 move_steps = steps * glm::normalize(glm::cross(camera_up, _front));

                    // update _target
                    _target = (camera_location + move_steps) + _front;

                    return move_steps;
                }
                
                glm::vec3 Right(const glm::vec3& camera_location, const glm::vec3& camera_up, GLfloat steps) override
                {
                    glm::vec3 move_steps = steps * glm::normalize(glm::cross(_front, camera_up));

                    // update _target
                    _target = (camera_location + move_steps) + _front;

                    return move_steps;
                }
            } _look_front_state;

            class LookAtState : public LookState
            {
            public:
                LookAtState()
                    : LookState()
                {
                }

                ~LookAtState()
                {
                }

                LookAtState(LookAtState&&) = default;
                LookAtState& operator=(LookAtState&&) = default;

                LookAtState(const LookAtState&) = default;
                LookAtState& operator=(const LookAtState&) = default;

                void Look(const glm::vec3& camera_location, const glm::vec3& vec) override
                {
                    _target = vec;

                    _front = glm::normalize(_target - camera_location);
                }

                void MoveTo(const glm::vec3& camera_location) override
                {
                    _front = glm::normalize(_target - camera_location);
                }

                glm::vec3 Forward(GLfloat steps) override
                {
                    return steps * _front;
                }

                glm::vec3 Backward(GLfloat steps) override
                {
                    return -1.0f * steps * _front;
                }
                
                glm::vec3 Left(const glm::vec3& camera_location, const glm::vec3& camera_up, GLfloat steps) override
                {
                    glm::vec3 move_steps = steps * glm::normalize(glm::cross(camera_up, _front));

                    // update _front
                    _front = glm::normalize(_target - (camera_location + move_steps));

                    return move_steps;
                }
                
                glm::vec3 Right(const glm::vec3& camera_location, const glm::vec3& camera_up, GLfloat steps) override
                {
                    glm::vec3 move_steps = steps * glm::normalize(glm::cross(_front, camera_up));

                    // update _front
                    _front = glm::normalize(_target - (camera_location + move_steps));

                    return move_steps;
                }
            } _look_at_state;

            LookState* _look_state;

            void fixPerspectiveFovy()
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

        public:
            explicit Camera(GLfloat aspect, GLfloat fovy = glm::radians(45.0f), GLfloat near = 0.1f, GLfloat far = 100.0f, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
            ~Camera();

            Camera(Camera&&);
            Camera& operator=(Camera&&);

            Camera(const Camera&);
            Camera& operator=(const Camera&);

            void MoveTo(GLfloat x, GLfloat y, GLfloat z);
            void MoveTo(const glm::vec3& location);

            void LookFront(GLfloat x, GLfloat y, GLfloat z);
            void LookFront(const glm::vec3& _front);
            
            void RotateTo(GLfloat yaw, GLfloat pitch);
            void Rotate(GLfloat yaw_adjusted, GLfloat pitch_adjusted);

            void LookAt(GLfloat x, GLfloat y, GLfloat z);
            void LookAt(const glm::vec3& _target);

            void SetPerspectiveAspect(GLfloat aspect);

            void SetPerspectiveFovyRange(GLfloat fovy_min, GLfloat fovy_max);
            void SetPerspectiveFovy(GLfloat fovy);
            void AdjustPerspectiveFovyDegree(GLfloat degree_adjusted);
            void AdjustPerspectiveFovyRadian(GLfloat radian_adjusted);

            void SetPerspectiveNear(GLfloat near);
            void SetPerspectiveFar(GLfloat far);

            const glm::mat4& GetProjection() {  return _projection; }

            void Forward(GLfloat steps);
            void Backward(GLfloat steps);
            void Left(GLfloat steps);
            void Right(GLfloat steps);

            glm::mat4 GetView() {  return glm::lookAt(_location, _look_state->GetTarget(), _up); }
        };
    }
}

#endif // GL_SIMPLIFY_CORE_CAMERA_H
