#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/basic/libglsimplify_sphere.h"

#include <iostream>

int test_sphere(int argc, char **argv, int width, int height)
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

        gl_simplify::scene::ScenePtr scene = CreateScene(width, height);

        if (!scene->Create(error, sizeof(error)))
        {
            std::cerr << "create scene error: " << error << std::endl;
            break;
        }

        gl_simplify::entity::basic::SpherePtr sphere = CreateSphereOf(1.0f, 64, 64);
        do
        {
            
            gl_simplify::core::Texture2DPtr texture = CreateTexture2D();
            texture->Build("resources/textures/eo_base_2020_clean_tn.jpg")->SetDefaultParameters();

            sphere->SetTexture(texture);
            
            scene->AddEntity(sphere);
        } while (false);

        gl_simplify::camera::BaseCameraPtr camera = scene->GetCamera();
        // 将相机放在上方和后方的位置
        camera->SetPosition(glm::vec3(0.0f, 3.0f, 5.0f));
        
        // 让相机看向平面中心 (0, 0, 0)
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

        window.SetScene(scene);

        window.Show([sphere, &window] (GLFWwindow*, gl_simplify::scene::ScenePtr scene) {
                // 使用帧时间实现匀速旋转
                GLfloat rotation_speed = 20.0f; // 每秒旋转20度
                sphere->Rotate(rotation_speed * window.GetDeltaTime(), glm::vec3(0.0f, 1.0f, 0.0f));
                scene->Render();
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
