

#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "material/libglsimplify_material_factory.h"

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

        scene.GetBackground().SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        gl_simplify::entity::Camera* camera = window.Camera();
        camera->Translate(glm::vec3(8.0f, 8.0f, 8.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        //camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        scene.GetLight()->TranslateTo(glm::vec3(0.0, 3.0, 3.0));
        scene.GetLight()->SetAmbient(glm::vec4(0.2, 0.2, 0.2, 1.0));
        scene.GetLight()->SetDiffuse(glm::vec4(0.5, 0.5, 0.5, 1.0));

        gl_simplify::material::SharedMaterial rock = gl_simplify::material::MaterialFactory::GetShared(gl_simplify::material::MaterialFactory::PredefinedMaterialType::PlasticWhite);

        gl_simplify::material::SharedMaterial wood = gl_simplify::material::MaterialFactory::GetShared(gl_simplify::material::MaterialFactory::PredefinedMaterialType::Chrome);
        //wood->SetTexture("resource/texture/wood.jpg");

        do
        {
            gl_simplify::entity::Plane* plane = new gl_simplify::entity::Plane();

            plane->Create();

            plane->Attatch(rock);
            plane->Translate(glm::vec3(0.0, -1.01, 0.0));
            plane->Scale(glm::vec3(24.0, 1.0, 24.0));
            
            scene.AddEntity(plane);
        } while (false);

        do
        {
            gl_simplify::material::SharedMaterial box_material = gl_simplify::material::MaterialFactory::Create("resource/texture/diffuse_cube.png", "resource/texture/specular_cube.png", 64.0f);
            gl_simplify::entity::Cube* cube = new gl_simplify::entity::Cube();

            cube->Create();

            cube->Attatch(box_material);
            cube->Translate(glm::vec3(-3.0, 0.0, 0.0));
            
            scene.AddEntity(cube);
        } while (false);

        do
        {
            gl_simplify::entity::Cylinder* cylinder = new gl_simplify::entity::Cylinder();

            cylinder->Create();

            cylinder->Attatch(wood);
            cylinder->Translate(glm::vec3(3.0, 0.0, 0.0));
            
            scene.AddEntity(cylinder);
        } while (false);

        do
        {
            gl_simplify::entity::Cone* cone = new gl_simplify::entity::Cone();

            cone->Create();

            cone->Attatch(wood);
            cone->Translate(glm::vec3(0.0, 0.0, -3.0));
            
            scene.AddEntity(cone);
        } while (false);

        double ts_pre = glfwGetTime();
        double r_interval = 0.002;

        window.Show([&scene, ts_pre, r_interval] (GLFWwindow*, gl_simplify::entity::Camera* camera) mutable {
                scene.Render(camera);

                double ts_curr = glfwGetTime();
                if (ts_pre + r_interval <= ts_curr)
                {
                    scene.GetLight()->RotateAround(0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
                    ts_pre = ts_curr;
                }
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
