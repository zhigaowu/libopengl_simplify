

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

        gl_simplify::scene::ScenePtr scene = std::make_shared<gl_simplify::scene::Scene>();

        if (!scene->Create(width, height, error, sizeof(error)))
        {
            std::cerr << "create scene error: " << error << std::endl;
            break;
        }

        gl_simplify::entity::CameraPtr camera = scene->GetCamera();
        camera->Translate(glm::vec3(16.0f, 16.0f, 16.0f));
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        //camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        gl_simplify::scene::Background& background = scene->GetBackground();
        //background.SetColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        if (!background.LoadSkyBox("resource/texture/skybox", error, sizeof(error)))
        {
            std::cerr << "load sky box for scene error: " << error << std::endl;
            break;
        }

        {
            scene->GetDirectionalLight()->TranslateTo(glm::vec3(0.0, 32.0, 0.0));

            scene->GetDirectionalLight()->SetDirection(glm::vec3(0.0, -1.0, -1.0));

#if true
            scene->GetDirectionalLight()->SetAmbient(glm::vec4(0.05f, 0.05f, 0.05f, 1.0));
            scene->GetDirectionalLight()->SetDiffuse(glm::vec4(0.4f, 0.4f, 0.4f, 1.0));
            scene->GetDirectionalLight()->SetSpecular(glm::vec4(0.5f, 0.5f, 0.5f, 1.0));
#else
            scene->GetDirectionalLight()->SetAmbient(glm::vec4(0.0f, 0.0f, 0.0f, 1.0));
            scene->GetDirectionalLight()->SetDiffuse(glm::vec4(0.0f, 0.0f, 0.0f, 1.0));
            scene->GetDirectionalLight()->SetSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0));
#endif
        }

#if true
        if (true)
        {
            gl_simplify::light::PointLightPtr point_light = scene->AddPointLight(glm::vec3(0.0, 8.0, 8.0));
            point_light->SetAmbient(glm::vec4(0.2, 0.8, 0.2, 1.0));
            point_light->SetDiffuse(glm::vec4(0.5, 0.8, 0.5, 1.0));
        }

        if (true)
        {
            gl_simplify::light::PointLightPtr point_light = scene->AddPointLight(glm::vec3(8.0, 8.0, 0.0));
            point_light->SetAmbient(glm::vec4(0.2, 0.2, 0.8, 1.0));
            point_light->SetDiffuse(glm::vec4(0.5, 0.5, 0.8, 1.0));
        }

        if (true)
        {
            gl_simplify::light::PointLightPtr point_light = scene->AddPointLight(glm::vec3(-8.0, 8.0, 0.0));
            point_light->SetAmbient(glm::vec4(0.8, 0.2, 0.2, 1.0));
            point_light->SetDiffuse(glm::vec4(0.8, 0.5, 0.5, 1.0));
        }
#endif

#if true

        if (true)
        {
            gl_simplify::light::SpotLightPtr spot_light = scene->AddSpotLight(glm::vec3(3.0, 16.0, 3.0));
            spot_light->SetAmbient(glm::vec4(1.0, 0.2, 0.2, 1.0));
            spot_light->SetDiffuse(glm::vec4(1.0, 0.5, 0.5, 1.0));
        }

        if (true)
        {
            gl_simplify::light::SpotLightPtr spot_light = scene->AddSpotLight(glm::vec3(-3.0, 16.0, 3.0));
            spot_light->SetAmbient(glm::vec4(0.2, 1.0, 0.2, 1.0));
            spot_light->SetDiffuse(glm::vec4(0.5, 1.0, 0.5, 1.0));
        }

        if (true)
        {
            gl_simplify::light::SpotLightPtr spot_light = scene->AddSpotLight(glm::vec3(3.0, 16.0, -3.0));
            spot_light->SetAmbient(glm::vec4(0.2, 0.2, 1.0, 1.0));
            spot_light->SetDiffuse(glm::vec4(0.5, 0.5, 1.0, 1.0));
        }

        if (true)
        {
            gl_simplify::light::SpotLightPtr spot_light = scene->AddSpotLight(glm::vec3(-3.0, 16.0, -3.0));
            spot_light->SetAmbient(glm::vec4(0.2, 0.2, 1.0, 1.0));
            spot_light->SetDiffuse(glm::vec4(1.0, 0.5, 5.0, 1.0));
        }

#endif

        gl_simplify::material::MaterialPtr rock = gl_simplify::material::MaterialFactory::Create("resource/texture/plane_rock.jpg", "resource/texture/plane_rock.jpg");

        gl_simplify::material::MaterialPtr wood = gl_simplify::material::MaterialFactory::Get(gl_simplify::material::MaterialFactory::PredefinedMaterialType::Ruby);

#if true
        do
        {
            gl_simplify::entity::PlanePtr plane = CreatePlane();

            plane->Create();

            plane->Attatch(rock);
            plane->Translate(glm::vec3(0.0, -1.01, 0.0));
            plane->Scale(glm::vec3(24.0, 1.0, 24.0));
            
            scene->AddEntity(plane);
        } while (false);
#endif

        do
        {
            gl_simplify::material::MaterialPtr box_material = gl_simplify::material::MaterialFactory::Create("resource/texture/diffuse_cube.png", "resource/texture/specular_cube.png", 64.0f);
            gl_simplify::entity::CubePtr cube = CreateCube();

            cube->Create();

            cube->Attatch(box_material);
            cube->Translate(glm::vec3(-3.0, 0.0, 0.0));
            
            scene->AddEntity(cube);
        } while (false);

        do
        {
            gl_simplify::entity::CylinderPtr cylinder = CreateCylinder();

            cylinder->SetSegments(256);
            cylinder->Create();

            cylinder->Attatch(wood);
            cylinder->Translate(glm::vec3(3.0, 0.0, 0.0));
            
            scene->AddEntity(cylinder);
        } while (false);

        do
        {
            gl_simplify::entity::ConePtr cone = CreateCone();

            cone->SetSegments(256);
            cone->Create();

            cone->Attatch(wood);
            cone->Translate(glm::vec3(0.0, 0.0, -3.0));
            
            scene->AddEntity(cone);
        } while (false);

        double ts_pre = glfwGetTime();
        double r_interval = 0.02;

        window.SetScene(scene);

        window.Show([ts_pre, r_interval] (GLFWwindow*, gl_simplify::scene::ScenePtr scene) mutable {
                scene->Render();

                double ts_curr = glfwGetTime();
                if (ts_pre + r_interval <= ts_curr)
                {
                    scene->GetSpotLight(0)->RotateAround(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
                    scene->GetSpotLight(1)->RotateAround(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
                    scene->GetSpotLight(2)->RotateAround(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
                    scene->GetSpotLight(3)->RotateAround(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
                    ts_pre = ts_curr;
                }
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
