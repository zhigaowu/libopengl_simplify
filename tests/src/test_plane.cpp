

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_plane.h"

#include <iostream>

int test_plane(int argc, char **argv, int width, int height)
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
            gl_simplify::entity::Plane* plane = new gl_simplify::entity::Plane();

            if (!plane->Initialize(error, sizeof(error)))
            {
                std::cout << "initialize plane failed: " << error << std::endl;

                delete plane;
                plane = nullptr;
                break;
            }

            if (!plane->Attach("../../resource/texture/plane_rock.jpg", error, sizeof(error)))
            {
                std::cout << "attach plane texture failed: " << error << std::endl;

                delete plane;
                plane = nullptr;
                break;
            }

            plane->Scale(glm::vec3(4.0, 0.0, 4.0));
            plane->Translate(glm::vec3(0.0, -8.0, 0.0));
            
            scene.AddEntity(plane);
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
