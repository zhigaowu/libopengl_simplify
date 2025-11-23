# 相机移动系统说明

## 步长参数的计算

在 `_default_callback_key_event_occurred` 中，相机移动的步长由以下因素决定：

### 影响因素

1. **基础移动速度 (`_camera_movement_speed`)**
   - 默认值：`2.5f` 单位/秒
   - 可通过 `SetCameraMovementSpeed(float)` 调整
   - 代表相机在场景中的移动速度（单位：场景单位/秒）

2. **帧时间差 (`_delta_time`)**
   - 当前帧与上一帧之间的时间差（单位：秒）
   - 自动在渲染循环中计算：`deltaTime = currentFrame - lastFrame`
   - 确保不同帧率下移动速度一致（帧率独立性）

3. **加速倍数 (`speed_multiplier`)**
   - 按住 Shift 键时：`2.0f`（双倍速度）
   - 正常情况：`1.0f`
   - 通过检测 `mods & GLFW_MOD_SHIFT` 判断

### 计算公式

```cpp
step_distance = _camera_control.GetDeltaMovement() * speed_multiplier
```

其中 `GetDeltaMovement()` 内部计算：
```cpp
GetDeltaMovement() = _camera_movement_speed * _delta_time
```

**示例计算：**
- 假设 FPS = 60，则 deltaTime ≈ 0.0167 秒
- 基础速度 = 2.5 单位/秒
- 不按 Shift：`step = 2.5 * 0.0167 * 1.0 = 0.04175` 单位/帧
- 按住 Shift：`step = 2.5 * 0.0167 * 2.0 = 0.0835` 单位/帧

## 使用方法

### 基本设置

```cpp
// 创建窗口
auto window = std::make_shared<Window>();
window->Create(800, 600, "OpenGL Window");

// 设置相机移动速度（可选，默认 2.5）
window->SetCameraMovementSpeed(5.0f);  // 更快的移动速度

// 设置鼠标旋转灵敏度（可选，默认 0.1）
window->SetCameraRotationSensitivity(0.15f);  // 更灵敏的旋转

// 设置场景
window->SetScene(scene);

// 开始渲染循环
window->Show();
```

### 键盘控制

- **W / ↑**: 前进（沿 front 方向）
- **S / ↓**: 后退（沿 front 反方向）
- **A / ←**: 左移（沿 right 反方向）
- **D / →**: 右移（沿 right 方向）
- **Shift + 移动键**: 加速移动（2倍速）
- **ESC**: 关闭窗口

**注意**：上下移动（Up/Down）方法已实现，但暂未绑定到键盘按键。可以通过代码调用 `camera->Up(step)` 和 `camera->Down(step)` 实现。

### 鼠标控制

- **右键拖拽**: 旋转相机视角（第一人称视角）
  - 水平拖拽：左右旋转（Yaw）
  - 垂直拖拽：上下旋转（Pitch）
- **鼠标灵敏度**: 默认 0.1，可通过 `SetCameraRotationSensitivity()` 调整

### 滚轮控制

- **滚轮向上**: 缩小 FOV（放大场景，类似望远镜效果）
- **滚轮向下**: 增大 FOV（缩小场景，类似广角镜头效果）
- **FOV 范围**: 限制在 1° 到 120° 之间
- **滚动灵敏度**: 每次滚动改变 0.1 弧度（约 5.7°）

**工作原理：**
- FOV（视野角度）越小 → 视野越窄 → 物体看起来越大（放大效果）
- FOV 越大 → 视野越宽 → 物体看起来越小（缩小效果）
- 默认 FOV：45°（glm::radians(45.0f)）

## 调整建议

根据场景规模调整移动速度：

```cpp
// 小场景（房间内部，范围 10x10 单位）
window->SetCameraMovementSpeed(1.0f);

// 中等场景（建筑，范围 100x100 单位）
window->SetCameraMovementSpeed(5.0f);

// 大场景（室外/地形，范围 1000x1000 单位）
window->SetCameraMovementSpeed(20.0f);
```

### 鼠标旋转灵敏度调整

```cpp
// 低灵敏度（精确控制）
window->SetCameraRotationSensitivity(0.05f);

// 默认灵敏度
window->SetCameraRotationSensitivity(0.1f);

// 高灵敏度（快速响应）
window->SetCameraRotationSensitivity(0.2f);
```

## 技术细节

### 帧率独立性

通过 `deltaTime` 保证不同帧率下移动距离一致：

```
30 FPS: 0.033s * 2.5 = 0.0825 单位/帧  →  30帧 = 2.475 单位/秒
60 FPS: 0.0167s * 2.5 = 0.04175 单位/帧  →  60帧 = 2.505 单位/秒
120 FPS: 0.0083s * 2.5 = 0.02075 单位/帧  →  120帧 = 2.49 单位/秒
```

### 方向计算与移动实现

相机提供了六个方向的移动方法：

1. **前后移动** (`Forward`/`Backward`)
   - 沿 `_front` 向量移动
   - 实现：`_position += _front * step.z`

2. **左右移动** (`Left`/`Right`)
   - 沿 `right = normalize(cross(_front, _up))` 向量移动
   - 实现：`_position += right * step.x`
   - 也可使用 `GetRight()` 方法获取右向量

3. **上下移动** (`Up`/`Down`)
   - 沿 `_up` 向量移动（世界坐标系 Y 轴）
   - 实现：`_position += _up * step.y`

这确保了相机总是沿着观察方向或世界轴移动，而不是屏幕坐标系。

### 鼠标旋转实现

鼠标右键拖拽实现第一人称视角旋转：

1. **水平旋转（Yaw）**
   - 围绕世界上方向（up 轴）旋转
   - 鼠标左右移动 → 视角左右转动
   
2. **垂直旋转（Pitch）**
   - 围绕相机的右方向（right 轴）旋转
   - right = normalize(cross(front, up))
   - 鼠标上下移动 → 视角上下转动

**旋转灵敏度计算：**
```cpp
rotation_angle = mouse_offset * sensitivity
```

示例：
- 鼠标移动 100 像素
- 灵敏度 0.1
- 旋转角度 = 100 * 0.1 = 10 度

### 相机控制 API

#### 位置和朝向设置

```cpp
// 设置相机位置
camera->SetPosition(glm::vec3(x, y, z));
glm::vec3 pos = camera->GetPosition();

// 让相机看向目标点（自动更新 front 向量）
camera->LookAt(glm::vec3(target_x, target_y, target_z));

// 直接设置朝向向量
camera->LookFront(glm::vec3(front_x, front_y, front_z));

// 获取相机方向向量
glm::vec3 front = camera->GetFront();
glm::vec3 up = camera->GetUp();
glm::vec3 right = camera->GetRight();
```

#### 移动方法

```cpp
glm::vec3 step(x_distance, y_distance, z_distance);

camera->Forward(step);   // 前进，使用 step.z
camera->Backward(step);  // 后退，使用 step.z
camera->Left(step);      // 左移，使用 step.x
camera->Right(step);     // 右移，使用 step.x
camera->Up(step);        // 上移，使用 step.y
camera->Down(step);      // 下移，使用 step.y
```

#### 旋转方法

```cpp
// 围绕 up 轴水平旋转（Yaw）
camera->Rotate(angle_degrees);

// 围绕指定轴旋转
camera->Rotate(axis, angle_degrees);
```

#### 视野控制

```cpp
// 设置 FOV（视野角度，弧度）
camera->SetFovy(glm::radians(60.0f));
GLfloat fov = camera->GetFovy();

// 设置 FOV 限制范围
camera->setFovyLimits(glm::radians(1.0f), glm::radians(120.0f));

// 设置宽高比
camera->SetAspect(width / height);
camera->SetKeepAspect(true);  // 是否保持宽高比
```

