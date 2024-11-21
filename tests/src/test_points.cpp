

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/point/libglsimplify_gl_point.h"

#include <iostream>

int test_points(int argc, char **argv, int width, int height)
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
            gl_simplify::entity::point::GLPoint* point = new gl_simplify::entity::point::GLPoint();

            if (!point->Initialize(error, sizeof(error)))
            {
                std::cout << "initialize point failed: " << error << std::endl;

                delete point;
                point = nullptr;
                break;
            }

            if (!point->Attach(glm::vec4(1.0, 0.0, 0.0, 1.0), error, sizeof(error)))
            {
                std::cout << "attach point color failed: " << error << std::endl;

                delete point;
                point = nullptr;
                break;
            }

            point->SetSize(100);
            
            scene.AddEntity(point);
        } while (false);

        scene.GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::Camera* camera = window.Camera();
        camera->Move(glm::vec3(0.0f, 0.0f, 8.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        //camera->LookFront(0.0f, 0.0f, -3.0f);

        window.Show([&scene] (GLFWwindow*, gl_simplify::entity::Camera* camera) {
                scene.Render(camera);
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
