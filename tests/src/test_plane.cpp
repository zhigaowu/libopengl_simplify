#include "glfw/libglsimplify_window.h"

#include "scene/libglsimplify_scene.h"

#include "entity/basic/libglsimplify_plane.h"

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

        gl_simplify::scene::ScenePtr scene = CreateScene(width, height);

        if (!scene->Create(error, sizeof(error)))
        {
            std::cerr << "create scene error: " << error << std::endl;
            break;
        }

        do
        {
            gl_simplify::entity::basic::PlanePtr plane = CreatePlaneOf(2.0f, 2.0f, 1, 1, GL_TRUE);

            //plane->SetColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

            // 不需要缩放和平移，保持在原点
            // plane->Scale(glm::vec3(4.0, 0.0, 4.0));
            // plane->Translate(glm::vec3(0.0, -8.0, 0.0));
            
            scene->AddEntity(plane);
        } while (false);

        gl_simplify::camera::BaseCameraPtr camera = scene->GetCamera();
        // 将相机放在上方和后方的位置
        camera->SetPosition(glm::vec3(0.0f, 3.0f, 5.0f));
        
        // 让相机看向平面中心 (0, 0, 0)
        camera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

        window.SetScene(scene);

        window.Show([] (GLFWwindow*, gl_simplify::scene::ScenePtr scene) {
                scene->Render();
            });

        res = 0;
    } while (false);

    window.Destroy();

    return res;
}
