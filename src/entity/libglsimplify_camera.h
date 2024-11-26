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

#ifndef GL_SIMPLIFY_ENTITY_CAMERA_H
#define GL_SIMPLIFY_ENTITY_CAMERA_H

#include "entity/libglsimplify_entity.h"

namespace gl_simplify {

    namespace entity {

        namespace {

            class ViewState
            {
            protected:
                Camera& _camera;

            protected:
                glm::vec3 _target;

            protected:
                glm::vec3 _front;

            protected:
                virtual void updateView() = 0;

            public:
                ViewState(Camera& camera);
                virtual ~ViewState();

                const glm::vec3& GetTarget() { return _target; }
                
                virtual void Look(const glm::vec3& vec) = 0;

                virtual void Move(const glm::vec3& step) = 0;

                virtual void Rotate(const glm::vec3& step) = 0;

                virtual void Forward() = 0;
                virtual void Backward() = 0;
                virtual void Left() = 0;
                virtual void Right() = 0;

            };
            
            // look in the front direction
            class FreeViewState : public ViewState
            {
            private:
                GLfloat _yaw;
                GLfloat _pitch;

            private:
                void updateView() override;

            public:
                FreeViewState(Camera& camera);
                ~FreeViewState();

                void Look(const glm::vec3& vec) override;

                void Move(const glm::vec3& step) override;

                void Rotate(const glm::vec3& step) override;

                void Forward() override;

                void Backward() override;
                
                void Left() override;
                
                void Right() override;
            };

            // keep the target in the view center
            class FocusViewState : public ViewState
            {
            private:
                void updateView() override;

            public:
                FocusViewState(Camera& camera);
                ~FocusViewState();

                void Look(const glm::vec3& target) override;

                void Move(const glm::vec3& step) override;

                void Rotate(const glm::vec3& step) override;

                void Forward() override;

                void Backward() override;
                
                void Left() override;
                
                void Right() override;
            };
        }

        class Camera : public Entity {
        private:
            glm::vec3 _up;

        private:
            GLfloat _move_sensitive;
            GLfloat _rotate_sensitive;

        private:
            GLfloat _min_fovy_radian;
            GLfloat _max_fovy_radian;

            glm::vec4 _projection_component;
            glm::mat4 _projection;

        private:
            friend class ViewState;
            friend class FreeViewState;
            friend class FocusViewState;

            FreeViewState _free_view_state;
            FocusViewState _focus_view_state;

            ViewState* _view_state;

        private:
            void fixPerspectiveFovy();

        public:
            explicit Camera(GLfloat aspect, GLfloat fovy = glm::radians(45.0f), GLfloat near = 0.1f, GLfloat far = 100.0f, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
            ~Camera();

            bool ResetDataBuffer(GLchar* error, GLsizei error_length) override;

            void LookAt(const glm::vec3& target);

            void LookFront(const glm::vec3& front);

            void Move(const glm::vec3& step);
            
            void Rotate(const glm::vec3& step);

            void Forward();
            void Backward();
            void Left();
            void Right();

            void SetPerspectiveAspect(GLfloat aspect);

            void SetPerspectiveFovyRange(GLfloat fovy_min, GLfloat fovy_max);
            void SetPerspectiveFovy(GLfloat fovy);
            void AdjustPerspectiveFovyDegree(GLfloat degree_adjusted);
            void AdjustPerspectiveFovyRadian(GLfloat radian_adjusted);

            void SetPerspectiveNear(GLfloat near);
            void SetPerspectiveFar(GLfloat far);

            const glm::mat4& GetProjection() const {  return _projection; }

            glm::mat4 GetView() const;
        };
    }
}

#endif // GL_SIMPLIFY_ENTITY_CAMERA_DEFAULT_CAMERA_H
