

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_cube.h"

#include "material/libglsimplify_material_factory.h"

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

        scene.GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::CameraPtr camera = window.Camera();
        camera->Translate(glm::vec3(0.0f, 3.0f, 3.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        //camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        scene.GetDirectionalLight()->TranslateTo(glm::vec3(2.0, 4.0, 4.0));
        scene.GetDirectionalLight()->SetSpecular(glm::vec4(0.0, 0.0, 0.0, 0.0));

        gl_simplify::material::SharedMaterial wood = gl_simplify::material::MaterialFactory::Create("resource/texture/diffuse_cube.png", "resource/texture/specular_cube.png");
        
        do
        {
            gl_simplify::entity::CubePtr cube = CreateCube();

            cube->Create();

            cube->Attatch(wood);
            
            scene.AddEntity(cube);
        } while (false);

        window.Show([&scene] (GLFWwindow*, gl_simplify::entity::CameraPtr camera) {
                scene.Render(camera);
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
