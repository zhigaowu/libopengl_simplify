

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_plane.h"

#include "material/libglsimplify_material_factory.h"

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

        gl_simplify::scene::ScenePtr scene = std::make_shared<gl_simplify::scene::Scene>();

        if (!scene->Create(width, height, error, sizeof(error)))
        {
            std::cerr << "create scene error: " << error << std::endl;
            break;
        }

        gl_simplify::material::MaterialPtr rock = gl_simplify::material::MaterialFactory::Create("resource/texture/diffuse_cube.png", "resource/texture/specular_cube.png");

        do
        {
            gl_simplify::entity::PlanePtr plane = CreatePlane();

            plane->Create();

            plane->Attatch(rock);
            plane->Scale(glm::vec3(4.0, 0.0, 4.0));
            plane->Translate(glm::vec3(0.0, -8.0, 0.0));
            
            scene->AddEntity(plane);
        } while (false);

        scene->GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::CameraPtr camera = scene->GetCamera();
        camera->Translate(glm::vec3(0.0f, 8.0f, 8.0f));
        camera->LookAt(glm::vec3(0.0f, 2.0f, 0.0f));
        //camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        window.SetScene(scene);

        window.Show([] (GLFWwindow*, gl_simplify::scene::ScenePtr scene) {
                scene->Render();
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
