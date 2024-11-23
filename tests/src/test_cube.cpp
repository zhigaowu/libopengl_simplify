

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_cube.h"

#include <iostream>

int test_cube(int argc, char **argv, int width, int height)
{
    int res = -1;

    gl_simplify::glfw::Window window;

    do
    {
        if (!window.Create(width, height, argv[1]))
        {
            break;
        }

        char error[128] = { 0 };

        gl_simplify::scene::Scene scene;

        if (!scene.Create(error, sizeof(error)))
        {
            std::cerr << "create scene error: " << error << std::endl;
            break;
        }

        do
        {
            gl_simplify::entity::Cube* cube = new gl_simplify::entity::Cube();

            if (!cube->Initialize(error, sizeof(error)))
            {
                std::cout << "initialize cube failed: " << error << std::endl;

                delete cube;
                cube = nullptr;
                break;
            }

            if (!cube->Attach("../../resource/texture/wood.jpg", error, sizeof(error)))
            {
                std::cout << "attach cube texture failed: " << error << std::endl;

                delete cube;
                cube = nullptr;
                break;
            }
            
            scene.AddEntity(cube);
        } while (false);

        scene.GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::Camera* camera = window.Camera();
        camera->Translate(glm::vec3(0.0f, 2.0f, 8.0f));
        //camera->LookAt(glm::vec3(0.0f, 2.0f, 0.0f));
        camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        window.Show([&scene] (GLFWwindow*, gl_simplify::entity::Camera* camera) {
                scene.Render(camera);
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
