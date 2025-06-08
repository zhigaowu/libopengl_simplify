/*
 * ==========================================================================
 *
 *       Filename:  libglsimplify_window.h
 *
 *    Description:  GLFW window logic
 *
 *        Version:  1.0
 *        Created:  2024-04-07 19:30:29
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#ifndef GL_SIMPLIFY_GLFW_WINDOW_H
#define GL_SIMPLIFY_GLFW_WINDOW_H

#include "core/libglsimplify_types.h"

#include "libglsimplify_mouse.h"

#include "scene/libglsimplify_scene.h"

#include <GLFW/glfw3.h>

#include <functional>

namespace gl_simplify {

    namespace glfw {

        using CallbackWindowSizeChanged = std::function<void(GLFWwindow*, int, int)>; // int width, int height

        using CallbackKeyEventOcurred = std::function<void(GLFWwindow*, int, int, int, int)>; // int key, int scancode, int action, int mods

        using CallbackMouseEntered = std::function<void(GLFWwindow*, int)>; // int entered
        using CallbackMouseClicked = std::function<void(GLFWwindow*, int, int, int)>; // int key, int action, int mods
        using CallbackMouseMoved = std::function<void(GLFWwindow*, double, double)>; // double xpos, double ypos

        using CallbackWheelScrolled = std::function<void(GLFWwindow*, double, double)>; // double xoffset, double yoffset

        using CallbackRenderWindow = std::function<void(GLFWwindow*, scene::ScenePtr)>;

        void Initialize(int glMajorVersion = 4, int glMinorVersion = 6);

        void Hint(int hint, int value);

        void Shutdown();

        class Window : private core::NonCopyable {
        public:
            Window();
            ~Window();

            GLFWwindow* Create(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

            void ShowCursor(bool show = true);

            void SetScene(scene::ScenePtr& scene)
            {
                _scene = scene;
            }

            void SetWindowSizeChangedCallback(const CallbackWindowSizeChanged& callback_window_size_changed)
            {
                _callback_window_size_changed = [this, callback_window_size_changed] (GLFWwindow* window, int width, int height) {
                    _default_callback_window_size_changed(window, width, height);
                    
                    callback_window_size_changed(window, width, height);
                };
            }

            void SetKeyEventCallback(const CallbackKeyEventOcurred& callback_key_event_occurred)
            {
                _callback_key_event_occurred = [this, callback_key_event_occurred] (GLFWwindow* window, int key, int scancode, int action, int mods) {
                    _default_callback_key_event_occurred(window, key, scancode, action, mods);

                    callback_key_event_occurred(window, key, scancode, action, mods);
                };
            }

            void SetMouseCallback(const CallbackMouseEntered& callback_mouse_entered,
                const CallbackMouseClicked& callback_mouse_clicked, 
                const CallbackMouseMoved& callback_mouse_moved)
            {
                _callback_mouse_entered = [this, callback_mouse_entered](GLFWwindow* window, int entered) {
                    _default_callback_mouse_entered(window, entered);
                    callback_mouse_entered(window, entered);
                };

                _callback_mouse_clicked = [this, callback_mouse_clicked](GLFWwindow* window, int key, int action, int mods) {
                    _default_callback_mouse_clicked(window, key, action, mods);
                    callback_mouse_clicked(window, key, action, mods);
                };

                _callback_mouse_moved = [this, callback_mouse_moved](GLFWwindow* window, double xpos, double ypos) {
                    _default_callback_mouse_moved(window, xpos, ypos);
                    callback_mouse_moved(window, xpos, ypos);
                };
            }

            void SetWheelScrollCallback(const CallbackWheelScrolled& callback_wheel_scrolled)
            {
                _callback_wheel_scrolled = [this, callback_wheel_scrolled] (GLFWwindow* window, double xoffset, double yoffset) {
                    _default_callback_wheel_scrolled(window, xoffset, yoffset);

                    callback_wheel_scrolled(window, xoffset, yoffset);
                };
            }
            
            void Show(const CallbackRenderWindow& callback_render_window = [] (GLFWwindow*, scene::ScenePtr) {});

            void Destroy();

        private:
            static void glfw_callback_framebuffer_size_changed(GLFWwindow* window, int width, int height);

            static void glfw_callback_key_event_changed(GLFWwindow* window, int key, int scancode, int action, int mods);

            static void glfw_callback_mouse_entered(GLFWwindow* window, int entered);
            static void glfw_callback_mouse_clicked(GLFWwindow* window, int button, int action, int mods);
            static void glfw_callback_mouse_moved(GLFWwindow* window, double xpos, double ypos);

            static void glfw_callback_wheel_scrolled(GLFWwindow* window, double xoffset, double yoffset);
        
        private:
            GLFWwindow* _window;

        private:
            GLFWmonitor* _monitor;
            GLFWwindow* _share;

        private:
            Mouse _mouse;
            scene::ScenePtr _scene;

        private:
            CallbackWindowSizeChanged _default_callback_window_size_changed;
            CallbackWindowSizeChanged _callback_window_size_changed;

        private:
            CallbackKeyEventOcurred _default_callback_key_event_occurred;
            CallbackKeyEventOcurred _callback_key_event_occurred;

        private:
            CallbackMouseEntered _default_callback_mouse_entered;
            CallbackMouseEntered _callback_mouse_entered;

        private:
            CallbackMouseClicked _default_callback_mouse_clicked;
            CallbackMouseClicked _callback_mouse_clicked;

        private:
            CallbackMouseMoved _default_callback_mouse_moved;
            CallbackMouseMoved _callback_mouse_moved;

        private:
            CallbackWheelScrolled _default_callback_wheel_scrolled;
            CallbackWheelScrolled _callback_wheel_scrolled;
        };
    }
}

#endif // GL_SIMPLIFY_GLFW_WINDOW_H
