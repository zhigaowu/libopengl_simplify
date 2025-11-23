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

            , _camera_control()

            , _mouse()

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
                _scene->GetCamera()->SetAspect((float)width / (float)height);
            };
            _callback_window_size_changed = _default_callback_window_size_changed; 

            _default_callback_key_event_occurred = [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
                // 只在按键按下或持续按下时处理
                if (action == GLFW_RELEASE) {
                    return;
                }

                // 计算步长：基础速度 * 帧时间 * 可选的加速倍数
                GLfloat speed_multiplier = (mods & GLFW_MOD_SHIFT) ? 2.0f : 1.0f;  // Shift 键加速
                GLfloat step_distance = _camera_control.GetDeltaMovement() * speed_multiplier;
                glm::vec3 step(step_distance, step_distance, step_distance);

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
                    _scene->GetCamera()->Forward(step);
                    break;
                }
                case GLFW_KEY_S:
                case GLFW_KEY_DOWN:
                {
                    _scene->GetCamera()->Backward(step);
                    break;
                }
                case GLFW_KEY_A:
                case GLFW_KEY_LEFT:
                {
                    _scene->GetCamera()->Left(step);
                    break;
                }
                case GLFW_KEY_D:
                case GLFW_KEY_RIGHT:
                {
                    _scene->GetCamera()->Right(step);
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
                else
                {
                    _mouse.left_button_down = false;
                }

                if (GLFW_MOUSE_BUTTON_RIGHT == key)
                {
                    _mouse.right_button_down = 1 == action;
                }
                else
                {
                    _mouse.right_button_down = false;
                }

                if (GLFW_MOUSE_BUTTON_MIDDLE == key)
                {
                    _mouse.middle_button_down = 1 == action;
                }
                else
                {
                    _mouse.middle_button_down = false;
                }
            };
            _callback_mouse_clicked = _default_callback_mouse_clicked;

            _default_callback_mouse_moved = [this] (GLFWwindow*, double xpos, double ypos) {
                // 计算鼠标移动偏移量
                GLfloat xoffset = static_cast<GLfloat>(xpos - _mouse.x);
                GLfloat yoffset = static_cast<GLfloat>(_mouse.y - ypos);  // y 坐标反转（屏幕坐标系是上到下）

                // 计算三维移动方向：x轴（右）、y轴（上）、z轴（移动距离）
                GLfloat move_distance = std::sqrt(xoffset * xoffset + yoffset * yoffset);
                _mouse.direction = glm::vec3(xoffset, yoffset, move_distance);

                // 更新鼠标位置
                _mouse.x = xpos;
                _mouse.y = ypos;

                // 右键拖拽：旋转相机视角（第一人称视角控制）
                if (_mouse.right_button_down)
                {
                    // 应用鼠标灵敏度
                    GLfloat adjusted_xoffset = xoffset * _camera_control.rotation_sensitivity;
                    GLfloat adjusted_yoffset = yoffset * _camera_control.rotation_sensitivity;

                    // 水平旋转（yaw）：围绕世界 up 轴旋转
                    if (adjusted_xoffset != 0.0f)
                    {
                        _scene->GetCamera()->Rotate(adjusted_xoffset);
                    }

                    // 垂直旋转（pitch）：围绕相机的 right 轴旋转
                    if (adjusted_yoffset != 0.0f)
                    {
                        _scene->GetCamera()->Rotate(_scene->GetCamera()->GetRight(), adjusted_yoffset);
                    }
                }

                // 中键拖拽：平移相机位置
                if (_mouse.middle_button_down)
                {
                    _scene->GetCamera()->Left(glm::vec3(xoffset * _camera_control.pan_speed, 0.0f, 0.0f));
                    _scene->GetCamera()->Down(glm::vec3(0.0f, yoffset * _camera_control.pan_speed, 0.0f));
                }
            };
            _callback_mouse_moved = _default_callback_mouse_moved;

            _default_callback_wheel_scrolled = [this](GLFWwindow*, double xoffset, double yoffset) {
                // 通过调整 FOV 实现缩放效果
                GLfloat fov = _scene->GetCamera()->GetFovy();
                GLfloat fov_change = static_cast<GLfloat>(yoffset) * _camera_control.fov_sensitivity;  // 每次滚动改变 0.1 弧度
                
                _scene->GetCamera()->SetFovy(fov - fov_change);
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
                // 计算帧时间差
                GLfloat current_frame = static_cast<GLfloat>(glfwGetTime());
                _camera_control.UpdateFrameTime(current_frame);

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

