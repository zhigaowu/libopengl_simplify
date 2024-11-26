

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_cube.h"
#include "entity/libglsimplify_plane.h"

#include "entity/libglsimplify_cylinder.h"
#include "entity/libglsimplify_cone.h"

#include <iostream>

int test_all(int argc, char **argv, int width, int height)
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

            if (!plane->Create(error, sizeof(error)))
            {
                std::cout << "create plane failed: " << error << std::endl;

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

            plane->Translate(glm::vec3(0.0, -1.01, 0.0));
            plane->Scale(glm::vec3(8.0, 1.0, 8.0));
            
            scene.AddEntity(plane);
        } while (false);

        do
        {
            gl_simplify::entity::Cube* cube = new gl_simplify::entity::Cube();

            if (!cube->Create(error, sizeof(error)))
            {
                std::cout << "create cube failed: " << error << std::endl;

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

            cube->Translate(glm::vec3(-3.0, 0.0, 0.0));
            
            scene.AddEntity(cube);
        } while (false);

        do
        {
            gl_simplify::entity::Cylinder* cylinder = new gl_simplify::entity::Cylinder();

            if (!cylinder->Create(error, sizeof(error)))
            {
                std::cout << "create cylinder failed: " << error << std::endl;

                delete cylinder;
                cylinder = nullptr;
                break;
            }

#if false
            if (!cylinder->Attach(glm::vec4(0.0, 0.5, 0.0, 0.9), error, sizeof(error)))
            {
                std::cout << "attach cylinder color failed: " << error << std::endl;

                delete cylinder;
                cylinder = nullptr;
                break;
            }
#else
            if (!cylinder->Attach("../../resource/texture/wood.jpg", error, sizeof(error)))
            {
                std::cout << "attach cylinder texture failed: " << error << std::endl;

                delete cylinder;
                cylinder = nullptr;
                break;
            }
#endif

            cylinder->Translate(glm::vec3(3.0, 0.0, 0.0));
            
            scene.AddEntity(cylinder);
        } while (false);

        do
        {
            gl_simplify::entity::Cone* cone = new gl_simplify::entity::Cone();

            if (!cone->Create(error, sizeof(error)))
            {
                std::cout << "create cone failed: " << error << std::endl;

                delete cone;
                cone = nullptr;
                break;
            }

#if false
            if (!cone->Attach(glm::vec4(0.0, 0.5, 0.0, 0.9), error, sizeof(error)))
            {
                std::cout << "attach cone color failed: " << error << std::endl;

                delete cone;
                cone = nullptr;
                break;
            }
#else
            if (!cone->Attach("../../resource/texture/wood.jpg", error, sizeof(error)))
            {
                std::cout << "attach cone texture failed: " << error << std::endl;

                delete cone;
                cone = nullptr;
                break;
            }
#endif

            cone->Translate(glm::vec3(0.0, 0.0, -3.0));
            
            scene.AddEntity(cone);
        } while (false);

        scene.GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::Camera* camera = window.Camera();
        camera->Translate(glm::vec3(0.0f, 7.0f, 7.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        //camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        window.Show([&scene] (GLFWwindow*, gl_simplify::entity::Camera* camera) {
                scene.Render(camera);
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
