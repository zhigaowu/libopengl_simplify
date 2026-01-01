/*
 * ==========================================================================
 *
 *       Filename:  test_sdf_text.cpp
 *
 *    Description:  Test SDF text rendering (Valve's signed distance field)
 *
 *        Version:  1.0
 *        Created:  2025-11-29 17:40:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Zhigao Wu, wuzhigaoem@163.com
 * ==========================================================================
 */

#include "glfw/libglsimplify_window.h"
#include "scene/libglsimplify_scene.h"

#include "entity/text/libglsimplify_text.h"

#include "renderer/text/libglsimplify_sdf_text_renderer.h"

#include <glad/glad.h>
#include <iostream>

using namespace gl_simplify;

int test_sdf_text(int argc, char **argv, int width, int height)
{
    int res = -1;

    // 创建窗口
    gl_simplify::glfw::Window window;

    do
    {
        if (!window.Create(width, height, argv[1]))
        {
            break;
        }

        // 创建场景
        char error[128] = { 0 };

        gl_simplify::scene::ScenePtr scene = CreateScene(width, height);

        // 在 Create 之前设置渲染器
        //scene->SetEntityRenderer(entity::EntityType::Text, CreateSDFTextRenderer());

        if (!scene->Create(error, sizeof(error)))
        {
            std::cerr << "create scene error: " << error << std::endl;
            break;
        }

        std::string error_message;
        // 加载字体并创建 SDF 字体图集
        gl_simplify::entity::text::TextParameter text_param;
        //text_param.font_path = "resources/fonts/JetBrainsMono-2.304/JetBrainsMono-Regular.ttf";
        text_param.font_path = "resources/fonts/System/STKAITI.TTF";
        text_param.font_height = 128;  // SDF基础纹理尺寸（降低可节省内存）
        text_param.render_both_faces = GL_TRUE;

        // 测试大尺寸渲染（SDF优势场景）
        // 原始位图：在这个尺寸下会模糊，需要128+像素的纹理
        // SDF：即使用64像素纹理，仍能保持清晰边缘
        gl_simplify::entity::text::TextPtr text = CreateTextOf(L"您好，字体渲染", 80, text_param);  // 80像素：比meta_size大，体现SDF优势
        if (!text->Generate(scene->GetTextRenderer()->GetCharacterGenerator(), &error_message))
        {
            std::cerr << "create text error: " << error_message << std::endl;
            break;
        }
        
        // 设置文本位置和颜色（在相机前方可见位置）
        text->TranslateTo(glm::vec3(-1.5f, 0.0f, -3.0f));  // 在相机前方3个单位，稍微偏左
        text->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // 红色文本，方便调试
        
        std::cout << "Text has " << text->GetCharacters().size() << " characters" << std::endl;
        
        scene->AddEntity(text);
        
        // 设置相机（透视投影）
        gl_simplify::camera::BaseCameraPtr camera = scene->GetCamera();
        camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        camera->LookFront(glm::vec3(0.0f, 0.0f, -1.0f));

        window.SetScene(scene);
        
        // 渲染循环
        window.Show([&](GLFWwindow*, scene::ScenePtr scene) {
            scene->Render();
        });
    } while (false);

    // 清理
    window.Destroy();

    return 0;
}
