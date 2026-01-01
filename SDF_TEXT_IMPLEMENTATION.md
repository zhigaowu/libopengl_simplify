# SDF 文本渲染实现

基于 Valve 的 SIGGRAPH 2007 论文 "Improved Alpha-Tested Magnification for Vector Textures and Special Effects" 实现的签名距离场（Signed Distance Field, SDF）文本渲染系统。

## 核心原理

### 什么是 SDF？

签名距离场是一种存储每个像素到最近边缘的距离的技术。在文本渲染中：
- **正值**：像素在字形内部，值表示到边缘的距离
- **负值**：像素在字形外部，值表示到边缘的距离
- **0.5**（归一化后）：表示边缘位置

### 优势

1. **高质量缩放**：可以任意放大而不失真
2. **锐利边缘**：使用 smoothstep 实现抗锯齿
3. **特效支持**：轮廓、阴影、发光等效果
4. **内存效率**：小纹理可以渲染大字体

## 实现组件

### 1. SDFFontAtlas - 字体图集生成器

```cpp
// 加载字体
auto font_atlas = std::make_shared<entity::text::SDFFontAtlas>();
font_atlas->LoadFont("arial.ttf", 48);  // 48 像素基础大小

// 预加载字符
font_atlas->PreloadCharacters(L"Hello World!");
```

**工作流程**：
1. 使用 FreeType 加载字体
2. 渲染字符位图
3. 计算每个像素的签名距离
4. 生成 OpenGL 纹理

### 2. SDFCharacter - 单个字符实体

```cpp
// 获取字符信息
const SDFCharacterInfo* info = font_atlas->GetCharacterInfo(L'A');

// 创建字符实体
auto character = std::make_shared<entity::text::SDFCharacter>(L'A', *info);
character->SetPosition2D(100.0f, 200.0f);
character->SetScale2D(2.0f);  // 2倍放大
character->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
```

### 3. SDFText - 文本字符串管理

```cpp
auto text = std::make_shared<entity::text::SDFText>(font_atlas);
text->SetText(L"Hello SDF!");
text->SetPosition(50.0f, 100.0f);
text->SetScale(1.5f);
text->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
```

### 4. SDFTextRenderer - 着色器渲染器

实现论文中的核心算法：

```glsl
// 片段着色器核心代码
float distance = texture(sdf_texture, TexCoord).r;
float edge_distance = 0.5;
float alpha = smoothstep(edge_distance - smoothness, 
                        edge_distance + smoothness, 
                        distance);
```

## 高级特效

### 轮廓效果

```cpp
text->SetOutlineWidth(0.2f);  // 轮廓宽度
text->SetOutlineColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));  // 黑色轮廓
```

**实现原理**：
- 在主边缘之前计算第二个边缘
- 在两个边缘之间填充轮廓颜色

### 边缘平滑度

```cpp
text->SetSmoothness(0.1f);  // 较小值 = 更锐利
text->SetSmoothness(0.3f);  // 较大值 = 更柔和
```

## 关键参数

### spread（扩散半径）

```cpp
// 在 SDFFontAtlas 构造函数中设置
_sdf_spread(8)  // 8 像素扩散
```

- **较小值**（4-8）：更精确但缩放能力有限
- **较大值**（16-32）：可以极度放大但精度降低

### smoothness（平滑度）

```cpp
text->SetSmoothness(0.1f);  // 推荐范围：0.05 - 0.3
```

- **0.05**：非常锐利，可能有锯齿
- **0.1**：标准质量（推荐）
- **0.3**：非常平滑，边缘可能模糊

### outline_width（轮廓宽度）

```cpp
text->SetOutlineWidth(0.2f);  // 范围：0.0 - 0.5
```

- **0.0**：无轮廓
- **0.1-0.2**：细轮廓
- **0.3-0.5**：粗轮廓

## 距离场计算算法

```cpp
float SDFFontAtlas::calculateDistance(const unsigned char* bitmap, 
                                      int width, int height, 
                                      int x, int y, 
                                      int max_distance)
{
    bool center_inside = bitmap[y * width + x] > 127;
    float min_distance = max_distance;
    
    // 搜索最近的边界
    for (int dy = -max_distance; dy <= max_distance; ++dy)
    {
        for (int dx = -max_distance; dx <= max_distance; ++dx)
        {
            // 检查是否为边界（内外过渡）
            if (center_inside != neighbor_inside)
            {
                float distance = sqrt(dx*dx + dy*dy);
                min_distance = min(min_distance, distance);
            }
        }
    }
    
    // 内部为正，外部为负
    return center_inside ? min_distance : -min_distance;
}
```

## 着色器实现细节

### 顶点着色器

```glsl
#version 460 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoord = texcoord;
}
```

### 片段着色器（基础版本）

```glsl
#version 460 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D sdf_texture;
uniform vec4 text_color;
uniform float smoothness;

void main()
{
    float distance = texture(sdf_texture, TexCoord).r;
    float alpha = smoothstep(0.5 - smoothness, 0.5 + smoothness, distance);
    FragColor = vec4(text_color.rgb, text_color.a * alpha);
}
```

### 片段着色器（带轮廓）

```glsl
// 主边缘
float alpha = smoothstep(0.5 - smoothness, 0.5 + smoothness, distance);

// 轮廓边缘
if (outline_width > 0.0)
{
    float outline_edge = 0.5 - outline_width;
    float outline_alpha = smoothstep(outline_edge - smoothness, 
                                    outline_edge + smoothness, 
                                    distance);
    
    // 混合颜色
    vec4 result_color = mix(outline_color, text_color, outline_alpha);
    FragColor = vec4(result_color.rgb, result_color.a * alpha);
}
```

## 性能优化

### 1. 字符预加载

```cpp
// 启动时预加载常用字符
font_atlas->PreloadCharacters(
    L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
);
```

### 2. 纹理缓存

所有生成的 SDF 纹理都缓存在 `SDFFontAtlas` 中，避免重复生成。

### 3. 渲染批处理

相同字体、相同参数的文本可以批量渲染。

## 使用示例

### 基础文本

```cpp
auto text = std::make_shared<entity::text::SDFText>(font_atlas);
text->SetText(L"Hello World!");
text->SetPosition(100.0f, 200.0f);
text->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

// 添加到场景
for (const auto& ch : text->GetCharacters())
{
    scene->AddEntity(ch);
}
```

### 标题文本（带轮廓）

```cpp
auto title = std::make_shared<entity::text::SDFText>(font_atlas);
title->SetText(L"GAME TITLE");
title->SetPosition(50.0f, 650.0f);
title->SetScale(3.0f);  // 大字体
title->SetColor(glm::vec4(1.0f, 0.8f, 0.0f, 1.0f));
title->SetOutlineWidth(0.15f);
title->SetOutlineColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
```

### 动态文本更新

```cpp
// 更新文本内容
text->SetText(L"Score: 1000");

// 重新添加到场景
scene->ClearEntities();
for (const auto& ch : text->GetCharacters())
{
    scene->AddEntity(ch);
}
```

## 扩展可能性

基于这个实现，可以添加：

1. **阴影效果**：双重采样距离场
2. **发光效果**：扩展外部距离的渲染
3. **渐变填充**：在片段着色器中使用渐变颜色
4. **动画效果**：基于时间修改 smoothness 或 outline_width
5. **3D 文本**：在 3D 空间中渲染

## 论文参考

Valve 的原始论文提出的关键创新：

1. **距离场存储**：使用单通道纹理存储距离
2. **Smoothstep 抗锯齿**：GPU 硬件加速的平滑边缘
3. **分辨率独立**：小纹理渲染大字体
4. **实时特效**：通过调整阈值实现轮廓等效果

完整论文：[SIGGRAPH 2007 - Improved Alpha-Tested Magnification](https://steamcdn-a.akamaihd.net/apps/valve/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf)
