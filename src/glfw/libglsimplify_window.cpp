
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

            glfwWindowHint(GLFW_STENCIL_BITS, 8);
            glfwWindowHint(GLFW_SAMPLES, 4);

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

            , _scene(nullptr)

            , _default_callback_window_size_changed()
            , _callback_window_size_changed()

            , _default_callback_key_event_occurred()
            , _callback_key_event_occurred()

            , _default_callback_mouse_entered()
            , _callback_mouse_entered()

            , _default_callback_mouse_clicked()
            , _callback_mouse_clicked()

            , _default_callback_mouse_moved()
            , _callback_mouse_moved()

            , _default_callback_wheel_scrolled()
            , _callback_wheel_scrolled()
        {
            _default_callback_window_size_changed = [this] (GLFWwindow* window, int width, int height) {
                // change viewport
                glViewport(0, 0, width, height);
                
                // change camera perspective
                _scene->GetCamera()->SetPerspectiveAspect((float)width / (float)height);
            };
            _callback_window_size_changed = _default_callback_window_size_changed; 

            _default_callback_key_event_occurred = [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
                switch (key)
                {
                case GLFW_KEY_ESCAPE:
                {
                    glfwSetWindowShouldClose(window, true);
                    break;
                }
                case GLFW_KEY_W:
                case GLFW_KEY_UP:
                {
                    _scene->GetCamera()->Forward();
                    break;
                }
                case GLFW_KEY_S:
                case GLFW_KEY_DOWN:
                {
                    _scene->GetCamera()->Backward();
                    break;
                }
                case GLFW_KEY_A:
                case GLFW_KEY_LEFT:
                {
                    _scene->GetCamera()->Left();
                    break;
                }
                case GLFW_KEY_D:
                case GLFW_KEY_RIGHT:
                {
                    _scene->GetCamera()->Right();
                    break;
                }
                default:
                    break;
                }
            };
            _callback_key_event_occurred = _default_callback_key_event_occurred; 

            _default_callback_mouse_entered = [this] (GLFWwindow*, int entered) {
                ;
            };
            _callback_mouse_entered = _default_callback_mouse_entered;

            _default_callback_mouse_clicked = [this] (GLFWwindow*, int key, int action, int mods) {
                if (GLFW_MOUSE_BUTTON_LEFT == key)
                {
                    _mouse.left_button_down = 1 == action;
                }

                if (GLFW_MOUSE_BUTTON_RIGHT == key)
                {
                    _mouse.right_button_down = 1 == action;
                }

                if (GLFW_MOUSE_BUTTON_MIDDLE == key)
                {
                    _mouse.middle_button_down = 1 == action;
                }
            };
            _callback_mouse_clicked = _default_callback_mouse_clicked;

            _default_callback_mouse_moved = [this] (GLFWwindow*, double xpos, double ypos) {
                if (_mouse.middle_button_down)
                {
                    _scene->GetCamera()->Move(glm::vec3(xpos - _mouse.x, ypos - _mouse.y, 0.0f));
                }

                if (_mouse.right_button_down)
                {
                    _scene->GetCamera()->Rotate(glm::vec3(0, xpos - _mouse.x, _mouse.y - ypos));
                }

                _mouse.x = xpos;
                _mouse.y = ypos;
            };
            _callback_mouse_moved = _default_callback_mouse_moved;

            _default_callback_wheel_scrolled = [this](GLFWwindow*, double xpos, double ypos) {
                _scene->GetCamera()->AdjustPerspectiveFovyDegree(-ypos);

                if (ypos > 0)
                {
                    _scene->GetCamera()->Forward();
                }
                else
                {
                    _scene->GetCamera()->Backward();
                }
            };
            _callback_wheel_scrolled = _default_callback_wheel_scrolled;
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

                glfwSetFramebufferSizeCallback(_window, Window::glfw_callback_framebuffer_size_changed);

                glfwSetKeyCallback(_window, Window::glfw_callback_key_event_changed);

                glfwSetCursorEnterCallback(_window, Window::glfw_callback_mouse_entered);
                glfwSetMouseButtonCallback(_window, Window::glfw_callback_mouse_clicked);
                glfwSetCursorPosCallback(_window, Window::glfw_callback_mouse_moved);

                glfwSetScrollCallback(_window, Window::glfw_callback_wheel_scrolled);

                // make glfwMakeContextCurrent invoke first;
                std::atomic_thread_fence(std::memory_order_acq_rel);

                gladLoadGL();
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
                callback_render_window(_window, _scene);

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

