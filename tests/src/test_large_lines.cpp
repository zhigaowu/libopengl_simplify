

#include "glfw/libglsimplify_window.h"

#include "core/libglsimplify_vertex_array.h"

#include "core/libglsimplify_texture_buffer.h"

#include "core/libglsimplify_camera.h"
#include "core/libglsimplify_program.h"

#include <iostream>

int test_large_lines(int argc, char **argv)
{
    int res = -1;

    gl_simplify::glfw::Window window;

    do
    {
        int width = 800;
        int height = 600;

        if (argc < 2)
        {
            std::cerr << "usage:" 
                << std::endl
                << argv[0] << " name width[800] height[600]" << std::endl;

            break;
        }

        if (argc >= 3)
        {
            width = atoi(argv[2]);
        }

        if (argc >= 4)
        {
            height = atoi(argv[3]);
        }

        gl_simplify::glfw::Initialize();

        if (!window.Create(width, height, argv[1]))
        {
            break;
        }

        //window.ShowCursor(false);

        char error[128] = { 0 };

        gl_simplify::core::Shader vertex_shader;
        gl_simplify::core::ShaderSource vertex_shader_source(
            "layout (location = 0) in vec2 vpos;"
            ""
            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"
            ""
            "void main()"
            "{" 
            "   gl_Position = projection * view * model * vec4(vpos, 0.0, 1.0);"
            "}");

        if (!vertex_shader.AddSource(vertex_shader_source).Compile(error, sizeof(error)))
        {
            std::cerr << "compile vertex shader: " << error << std::endl;
            break;
        }

        gl_simplify::core::Shader fragment_shader(GL_FRAGMENT_SHADER);
        gl_simplify::core::ShaderSource fragment_shader_source(
            "out vec4 FragColor;"
            ""
            "uniform vec4 vcolor;"
            ""
            "void main()"
            "{"
            "   FragColor = vcolor;"
            "}");

        if (!fragment_shader.AddSource(fragment_shader_source).Compile(error, sizeof(error)))
        {
            std::cerr << "compile fragment shader: " << error << std::endl;
            break;
        }

        gl_simplify::core::Program program;

        if (!program.Attach(vertex_shader).Attach(fragment_shader).Link(error, sizeof(error)))
        {
            std::cerr << "link program: " << error << std::endl;
            break;
        }

        program.Use([](gl_simplify::core::Program& program) {
            program.GetVariable("model").SetMat(glm::mat4(1.0f));
            program.GetVariable("vcolor").SetValue(0.0f, 1.0f, 0.0f, 1.0f);
        });

        // create transformations
        gl_simplify::core::Program::Variable view = program.GetVariable("view");
        gl_simplify::core::Program::Variable projection = program.GetVariable("projection");

        gl_simplify::core::BufferArray vbo;
        gl_simplify::core::VertexArray vao;

        static const size_t point_count = 1024 * 1024;

        static int32_t line_len = 5;

        vao.Bind([&vbo, width, height] (gl_simplify::core::VertexArray&) {
            int32_t left = -(point_count >> 1) * line_len;
            std::vector<float> point_data(point_count * 2);
            for (size_t i = 0; i < point_count; i++)
            {
                point_data[(i << 1)] = (float)(left) / (width >> 1);
                point_data[(i << 1) + 1] = (float)(std::rand() % height - (height >> 1)) / (height >> 1);

                left += line_len;
            }
            
            vbo.Bind();
            vbo.Upload(sizeof(float) * point_data.size(), point_data.data(), GL_STATIC_DRAW);
            vbo.SetAttribute(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        });

        vao.Unbind();

        gl_simplify::core::Camera camera((float)width / (float)height);
        camera.MoveTo(0.0f, 0.0f, 1.0f);
        //camera.LookAt(0.0f, 0.0f, 0.0f);
        camera.LookFront(0.0f, 0.0f, -3.0f);
        camera.SetOrtho(0.0, width, 0, height, -10.00f, 10.0f);

        glEnable(GL_DEPTH_TEST);
        glLineWidth(3.0);

        window.SetWindowSizeChangedCallback([&camera] (GLFWwindow*, int width, int height) {
            glViewport(0, 0, width, height);
            
            camera.SetPerspectiveAspect((float)width / (float)height);
        });

        window.SetKeyEventCallback([&camera](GLFWwindow* window, int key, int scancode, int action, int mods) {
            static const float transform_steps = 0.05f;
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window, true);
                break;
            }
            case GLFW_KEY_W:
            {
                camera.Forward(transform_steps);
                break;
            }
            case GLFW_KEY_S:
            {
                camera.Backward(transform_steps);
                break;
            }
            case GLFW_KEY_A:
            {
                camera.Left(transform_steps);
                break;
            }
            case GLFW_KEY_D:
            {
                camera.Right(transform_steps);
                break;
            }
            default:
                break;
            }
        });

        int mouse_button_down = -1;

        float lastX = 0.0f, lastY = 0.0f;

        window.SetMouseCallback([] (GLFWwindow*, int entered) {
            //std::cout << "Mouse click: " << key << ", action: "<< action << ", mods: " << mods << std::endl;
        },
        [&mouse_button_down] (GLFWwindow*, int key, int action, int mods) {
             if (1 == action)
             {
                mouse_button_down = key; // mouse_button_down = GLFW_MOUSE_BUTTON_RIGHT == key && 1 == action;
             }
             else
             {
                mouse_button_down = -1;
             }
        },
        [&mouse_button_down, &lastX, &lastY, &camera] (GLFWwindow*, double xpos, double ypos) {
            switch (mouse_button_down)
            {
            case GLFW_MOUSE_BUTTON_RIGHT:
            {
                float xoffset = xpos - lastX;
                float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

                const float sensitivity = 0.1f;
                xoffset *= sensitivity;
                yoffset *= sensitivity;

                camera.Rotate(xoffset, yoffset);
                break;
            }
            }
            lastX = xpos, lastY = ypos;
        });

        window.SetWheelScrollCallback([&camera] (GLFWwindow*, double xoffset, double yoffset) {
            camera.AdjustPerspectiveFovyDegree(-yoffset);
        });

        window.Show([&program, &vao, &view, &projection, &camera] (GLFWwindow* window) {

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                program.Use([&view, &projection, &camera] (gl_simplify::core::Program& program) {
                    view.SetMat(camera.GetView());
                    projection.SetMat(camera.GetProjection());
                });

                vao.Bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

                glDrawArrays(GL_LINE_STRIP, 0, point_count);
            });

        res = 0;
    } while (false);

    window.Destroy();

    gl_simplify::glfw::Shutdown();

    if (res < 0)
    {
        std::cout << "Input any key to exit ..." << std::endl;
        std::cin >> argc;
    }

    return res;
}
