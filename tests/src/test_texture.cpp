

#include "glfw/libglsimplify_window.h"

#include "core/libglsimplify_vertex_array.h"

#include "core/libglsimplify_texture_buffer.h"

#include "core/libglsimplify_program.h"

#include <iostream>

int test_texture(int argc, char **argv) 
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

        char error[128] = { 0 };

        gl_simplify::core::Shader vertex_shader;
        gl_simplify::core::ShaderSource vertex_shader_source(
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec3 aColor;"
            "layout (location = 2) in vec2 aTexCoord;"
            ""
            "out vec2 TexCoord;"
            "out vec3 ourColor;"
            "void main()"
            "{" 
            "   gl_Position = vec4(aPos, 1.0);"
            "   ourColor = aColor;"
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
            "in vec3 ourColor;"
            "in vec2 TexCoord;"
            ""
            "uniform sampler2D texture1;"
            "uniform sampler2D texture2;"
            ""
            "void main()"
            "{"
            "   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4) * vec4(ourColor, 1.0);"
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

        gl_simplify::core::BufferArray vbo;
        gl_simplify::core::BufferArray ebo(GL_ELEMENT_ARRAY_BUFFER);
        gl_simplify::core::VertexArray vao;

        vao.Bind([&vbo, &ebo] (gl_simplify::core::VertexArray&) {
            unsigned int indices[] = {  // note that we start from 0!
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };
            ebo.Bind();
            ebo.Upload(sizeof(indices), indices, GL_STATIC_DRAW);

            float vertices[] = {
                // positions          // colors           // texture coords
                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
            };
            vbo.Bind();
            vbo.Upload(sizeof(vertices), vertices, GL_STATIC_DRAW);
            vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            vbo.SetAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            vbo.SetAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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

        window.SetWindowSizeChangedCallback([] (GLFWwindow*, int width, int height) {
            glViewport(0, 0, width, height);
        });

        window.SetKeyEventCallback([](GLFWwindow* window, int key, int scancode, int action, int mods){
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window, true);
                break;
            }
            default:
            {}
            }
        });

        window.Show([&program, &vao, &texture1, &texture2] (GLFWwindow* window) {

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                texture1.Bind(GL_TEXTURE0);
                texture2.Bind(GL_TEXTURE1);
                
                program.Use();

                vao.Bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
                //glDrawArrays(GL_TRIANGLES, 0, 6);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
