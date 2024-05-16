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

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include <functional>

namespace gl_simplify {

    namespace glfw {

        using CallbackWindowSizeChanged = std::function<void(GLFWwindow*, int, int)>; // int width, int height

        using CallbackKeyEventOcurred = std::function<void(GLFWwindow*, int, int, int, int)>; // int key, int scancode, int action, int mods

        using CallbackMouseEntered = std::function<void(GLFWwindow*, int)>; // int entered
        using CallbackMouseClicked = std::function<void(GLFWwindow*, int, int, int)>; // int key, int action, int mods
        using CallbackMouseMoved = std::function<void(GLFWwindow*, double, double)>; // double xpos, double ypos

        using CallbackWheelScrolled = std::function<void(GLFWwindow*, double, double)>; // double xoffset, double yoffset

        using CallbackRenderWindow = std::function<void(GLFWwindow*)>;

        void Initialize(int glMajorVersion = 4, int glMinorVersion = 6);

        void Hint(int hint, int value);

        void Shutdown();

        class Window {
        public:
            Window();
            ~Window();

            GLFWwindow* Create(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

            void ShowCursor(bool show = true);

            void SetWindowSizeChangedCallback(const CallbackWindowSizeChanged& callback_window_size_changed)
            {
                _callback_window_size_changed = callback_window_size_changed;
            }

            void SetKeyEventCallback(const CallbackKeyEventOcurred& callback_key_event_occurred)
            {
                _callback_key_event_occurred = callback_key_event_occurred;
            }

            void SetMouseCallback(const CallbackMouseEntered& callback_mouse_entered,
                const CallbackMouseClicked& callback_mouse_clicked, 
                const CallbackMouseMoved& callback_mouse_moved)
            {
                _callback_mouse_entered = callback_mouse_entered;
                _callback_mouse_clicked = callback_mouse_clicked;
                _callback_mouse_moved = callback_mouse_moved;
            }

            void SetWheelScrollCallback(const CallbackWheelScrolled& callback_wheel_scrolled)
            {
                _callback_wheel_scrolled = callback_wheel_scrolled;
            }
            
            void Show(const CallbackRenderWindow& callback_render_window = [] (GLFWwindow*) {});

            void Destroy();

        public:
            Window(Window&&) = delete;
            Window& operator=(Window&&) = delete;

            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

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
            CallbackWindowSizeChanged _callback_window_size_changed;

        private:
            CallbackKeyEventOcurred _callback_key_event_occurred;

        private:
            CallbackMouseEntered _callback_mouse_entered;
            CallbackMouseClicked _callback_mouse_clicked;
            CallbackMouseMoved _callback_mouse_moved;

        private:
            CallbackWheelScrolled _callback_wheel_scrolled;
        };
    }
}

#endif // GL_SIMPLIFY_GLFW_WINDOW_H
