/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_base_camera.h
 *
 *    Description:  base camera interface
 *
 *        Version:  1.0
 *        Created:  2025-11-22 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_ENTITY_CAMERA_BASE_CAMERA_H
#define GL_SIMPLIFY_ENTITY_CAMERA_BASE_CAMERA_H

#include "entity/libglsimplify_base_entity.h"

namespace gl_simplify {

    namespace camera {

        class BaseCamera : private core::NonCopyable {
        private:
            GLfloat _aspect;
            GLfloat _fovy;
            GLfloat _near;
            GLfloat _far;

        protected:
            glm::vec3 _position;
            glm::vec3 _up;

        protected:
            glm::vec3 _front;
            glm::vec3 _target;

        protected:
            entity::BaseEntityPtr _entity;

        private:
            bool _keep_aspect;

        private:
            GLfloat _fovy_min;
            GLfloat _fovy_max;

        public:
            explicit BaseCamera(GLfloat aspect, GLfloat fovy = glm::radians(45.0f), GLfloat near = 0.1f, GLfloat far = 100.0f, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
            virtual ~BaseCamera();

            GLfloat GetAspect() const { return _aspect; }
            void SetAspect(GLfloat aspect);
            void SetKeepAspect(bool keep) { _keep_aspect = keep; }

            GLfloat GetFovy() const { return _fovy; }
            void SetFovy(GLfloat fovy);

            void setFovyLimits(GLfloat fovy_min, GLfloat fovy_max);

            GLfloat GetNear() const { return _near; }
            void SetNear(GLfloat near);

            GLfloat GetFar() const { return _far; }
            void SetFar(GLfloat far);

            const glm::vec3& GetPosition() const { return _position; }
            void SetPosition(const glm::vec3& position);

            const glm::vec3& GetFront() const { return _front; }
            const glm::vec3& GetUp() const { return _up; }
            const glm::vec3 GetRight() const { return glm::normalize(glm::cross(_front, _up)); }

            virtual void LookAt(const glm::vec3& target);

            virtual void LookFront(const glm::vec3& front);

            virtual void Forward(const glm::vec3& step) = 0;
            virtual void Backward(const glm::vec3& step) = 0;

            virtual void Left(const glm::vec3& step) = 0;
            virtual void Right(const glm::vec3& step) = 0;
            
            virtual void Up(const glm::vec3& step) = 0;
            virtual void Down(const glm::vec3& step) = 0;

            virtual void Rotate(GLfloat angle) = 0;

            virtual void Rotate(const glm::vec3& axis,GLfloat angle) = 0;

            glm::mat4 GetView() const;
            glm::mat4 GetProjection() const;
        };

        using BaseCameraPtr = std::shared_ptr<BaseCamera>;
    }
}

#endif // GL_SIMPLIFY_CAMERA_BASE_CAMERA_H
