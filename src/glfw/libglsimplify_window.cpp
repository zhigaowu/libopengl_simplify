
#include "libglsimplify_window.h"

#include <atomic>

namespace gl_simplify {

    namespace glfw {

        void Initialize(int glMajorVersion/* = 4*/, int glMinorVersion/* = 6*/)
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        }

        void Shutdown()
        {
            glfwTerminate();
        }

        void Hint(int hint, int value)
        {
            glfwWindowHint(hint, value);
        }

        Window::Window()
            : _window(nullptr)

            , _monitor(nullptr)
            , _share(nullptr)

            , _callback_window_size_changed()

            , _callback_key_event_occurred()

            , _callback_mouse_entered()
            , _callback_mouse_clicked()
            , _callback_mouse_moved()

            , _callback_wheel_scrolled()
        {
        }

        Window::~Window()
        {
        }

        GLFWwindow* Window::Create(int width, int height, const char* title, GLFWmonitor* monitor/* = nullptr*/, GLFWwindow* share/* = nullptr*/)
        {
            if ((_window = glfwCreateWindow(width, height, title, monitor, share)))
            {
                _monitor = monitor;
                _share = share;

                glfwSetWindowUserPointer(_window, this);

                glfwMakeContextCurrent(_window);

                // make glfwMakeContextCurrent invoke first;
                std::atomic_thread_fence(std::memory_order_acq_rel);

                gladLoadGL();

                glfwSetFramebufferSizeCallback(_window, Window::glfw_callback_framebuffer_size_changed);

                glfwSetKeyCallback(_window, Window::glfw_callback_key_event_changed);

                glfwSetCursorEnterCallback(_window, Window::glfw_callback_mouse_entered);
                glfwSetMouseButtonCallback(_window, Window::glfw_callback_mouse_clicked);
                glfwSetCursorPosCallback(_window, Window::glfw_callback_mouse_moved);

                glfwSetScrollCallback(_window, Window::glfw_callback_wheel_scrolled);
            }

            return _window;
        }

        void Window::ShowCursor(bool show)
        {
            if (show)
            {
                glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
        }

        void Window::Show(const CallbackRenderWindow &callback_render_window)
        {
            while (!glfwWindowShouldClose(_window))
            {
                // render window
                callback_render_window(_window);

                // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
                // -------------------------------------------------------------------------------
                glfwSwapBuffers(_window);
                glfwPollEvents();
            }
        }

        void Window::Destroy()
        {
            if (_window)
            {
                glfwDestroyWindow(_window);

                _window = nullptr;
            }
        }

        void Window::glfw_callback_framebuffer_size_changed(GLFWwindow *window, int width, int height)
        {
            CallbackWindowSizeChanged& callback = ((Window*)(glfwGetWindowUserPointer(window)))->_callback_window_size_changed;
            if (callback)
            {
                callback(window, width, height);
            }
        }

        void Window::glfw_callback_key_event_changed(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            CallbackKeyEventOcurred& callback = ((Window*)(glfwGetWindowUserPointer(window)))->_callback_key_event_occurred;
            if (callback)
            {
                callback(window, key, scancode, action, mods);
            }
        }

        void Window::glfw_callback_mouse_entered(GLFWwindow *window, int entered)
        {
            CallbackMouseEntered& callback = ((Window*)(glfwGetWindowUserPointer(window)))->_callback_mouse_entered;
            if (callback)
            {
                callback(window, entered);
            }
        }

        void Window::glfw_callback_mouse_clicked(GLFWwindow *window, int button, int action, int mods)
        {
            CallbackMouseClicked& callback = ((Window*)(glfwGetWindowUserPointer(window)))->_callback_mouse_clicked;
            if (callback)
            {
                callback(window, button, action, mods);
            }
        }

        void Window::glfw_callback_mouse_moved(GLFWwindow *window, double xpos, double ypos)
        {
            CallbackMouseMoved& callback = ((Window*)(glfwGetWindowUserPointer(window)))->_callback_mouse_moved;
            if (callback)
            {
                callback(window, xpos, ypos);
            }
        }

        void Window::glfw_callback_wheel_scrolled(GLFWwindow *window, double xoffset, double yoffset)
        {
            CallbackWheelScrolled& callback = ((Window*)(glfwGetWindowUserPointer(window)))->_callback_wheel_scrolled;
            if (callback)
            {
                callback(window, xoffset, yoffset);
            }
        }
    }
}

