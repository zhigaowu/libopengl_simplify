

#include "glfw/libglsimplify_window.h"

#include "core/libglsimplify_vertex_array.h"

#include "core/libglsimplify_texture_buffer.h"

#include "core/libglsimplify_camera.h"
#include "core/libglsimplify_program.h"

#include <iostream>

int test_camera(int argc, char **argv) 
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

        window.ShowCursor(false);

        char error[128] = { 0 };

        gl_simplify::core::Shader vertex_shader;
        gl_simplify::core::ShaderSource vertex_shader_source(
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec2 aTexCoord;"
            ""
            "out vec2 TexCoord;"
            ""
            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"
            ""
            "void main()"
            "{" 
            "   gl_Position = projection * view * model * vec4(aPos, 1.0);"
            "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);"
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
            "in vec2 TexCoord;"
            ""
            "uniform sampler2D texture1;"
            "uniform sampler2D texture2;"
            "void main()"
            "{"
            "   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);"
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
            program.GetVariable("texture1").SetValue(0);
            program.GetVariable("texture2").SetValue(1);
        });

        // create transformations
        gl_simplify::core::Program::Variable model = program.GetVariable("model");
        gl_simplify::core::Program::Variable view = program.GetVariable("view");
        gl_simplify::core::Program::Variable projection = program.GetVariable("projection");

        gl_simplify::core::BufferArray vbo;
        gl_simplify::core::VertexArray vao;

        vao.Bind([&vbo] (gl_simplify::core::VertexArray&) {
            float vertices[] = {
                // positions          // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };
            vbo.Bind();
            vbo.Upload(sizeof(vertices), vertices, GL_STATIC_DRAW);
            vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        });

        vao.Unbind();

        gl_simplify::core::TextureBuffer texture_buffer(2);
        gl_simplify::core::TextureBuffer::Texture& texture1 = texture_buffer
            .GetTexture(0)
            .Bind()
            .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
            .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
            .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
            .UploadImage("D:/Downloads/Chrome/texture1.jpg");

        gl_simplify::core::TextureBuffer::Texture& texture2 = texture_buffer
            .GetTexture(1)
            .Bind()
            .SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)
            .SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT)
            .SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            .SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
            .UploadImage("D:/Downloads/Chrome/texture2.png", 0, 0, GL_RGB, 0, GL_RGBA);

        gl_simplify::core::Camera camera((float)width / (float)height);
        camera.MoveTo(0.0f, 0.0f, 3.0f);
        //camera.LookAt(0.0f, 0.0f, 0.0f);
        camera.LookFront(0.0f, 0.0f, -3.0f);

        glEnable(GL_DEPTH_TEST);

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

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

        window.Show([&program, &vao, &cubePositions, &texture1, &texture2, &model, &view, &projection, &camera] (GLFWwindow* window) {

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                texture1.Bind(GL_TEXTURE0);
                texture2.Bind(GL_TEXTURE1);
                
                program.Use([&model, &view, &projection, &camera] (gl_simplify::core::Program& program) {
                    view.SetMat(camera.GetView());
                    projection.SetMat(camera.GetProjection());
                });

                vao.Bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
                for (unsigned int i = 0; i < 10; i++)
                {
                    // calculate the model matrix for each object and pass it to shader before drawing
                    glm::mat4 model_matrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    model_matrix = glm::translate(model_matrix, cubePositions[i]);
                    float angle = 20.0f * i;
                    model_matrix = glm::rotate(model_matrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                    model.SetMat(model_matrix);

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
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
