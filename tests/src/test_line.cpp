

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/libglsimplify_line.h"

#include "material/libglsimplify_material_factory.h"

#include <iostream>

int test_line(int argc, char **argv, int width, int height)
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

        int segments = 32;
        if (argc >= 5)
        {
            segments = atoi(argv[4]);
        }

        scene->GetDirectionalLight()->TranslateTo(glm::vec3(2.0, 4.0, 4.0));

        gl_simplify::material::MaterialPtr wood = gl_simplify::material::MaterialFactory::Get(gl_simplify::material::MaterialFactory::PredefinedMaterialType::Chrome);

        do
        {
            gl_simplify::entity::LinePtr line = CreateLine();

            line->SetSegments(segments);
            line->Create();
            line->Attatch(wood);
            
            scene->AddEntity(line);
        } while (false);

        scene->GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::CameraPtr camera = scene->GetCamera();
        camera->Translate(glm::vec3(0.0f, 2.0f, 8.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        window.SetScene(scene);

        window.Show([] (GLFWwindow*, gl_simplify::scene::ScenePtr scene) {
                scene->Render();
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
