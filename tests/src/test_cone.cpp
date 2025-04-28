

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_cone.h"

#include "material/libglsimplify_material_factory.h"

#include <iostream>

int test_cone(int argc, char **argv, int width, int height)
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

        int segments = 32;
        if (argc >= 5)
        {
            segments = atoi(argv[4]);
        }

        scene.GetDirectionalLight()->TranslateTo(glm::vec3(2.0, 4.0, 4.0));

        gl_simplify::material::MaterialPtr wood = gl_simplify::material::MaterialFactory::Get(gl_simplify::material::MaterialFactory::PredefinedMaterialType::Chrome);
        //wood->SetTexture("resource/texture/wood.jpg");

        do
        {
            gl_simplify::entity::ConePtr cone = CreateCone();

            cone->SetSegments(segments);
            cone->Create();
            cone->Attatch(wood);
            
            scene.AddEntity(cone);
        } while (false);

        scene.GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::CameraPtr camera = window.Camera();
        camera->Translate(glm::vec3(0.0f, 2.0f, 8.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        //camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        window.Show([&scene] (GLFWwindow*, gl_simplify::entity::CameraPtr camera) {
                scene.Render(camera);
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
