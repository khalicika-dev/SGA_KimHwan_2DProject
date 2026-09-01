// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

// Windows 헤더 파일
#include <windows.h>
#include <stdarg.h>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>
#include <assert.h>

// C 런타임 헤더 파일입니다.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

// DirectXTex
#include "../DirectXTex/DirectXTex.h"

// IMGUI
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_dx11.h"
#include "../ImGUI/imgui_impl_win32.h"

#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;

// Type
#include "TypeDef.h"

// Header File
#include "Framework/Device/Device.h"

#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"

#include "Framework/Render/VertexLayouts.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/Texture.h"

// Render
#include "Framework/State/SamplerState.h"
#include "Framework/State/BlendState.h"
#include "Framework/State/RasterizerState.h"
#include "Framework/State/StateManager.h"


// Utility
#include "Framework/Utility/Keyboard.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/DirectWrite.h"
#include "Framework/Utility/Debugger.h"

// Math
#include "Framework/Math/Math.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

// Collision
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/LineCollider.h"

#include "Framework/Animation/Action.h"
#include "Framework/Camera/Camera.h"

// Obj
#include "Object/Basic.Obj/Quad.h"
#include "Object/Basic.Obj/Sprite.h"
#include "Object/Basic.Obj/Button.h"

#include "Object/Basic.Obj/Effect/Effect.h"
#include "Object/Basic.Obj/Effect/EffectManager.h"

// GameObj
#include "Object/GameObj/Base/MapManager.h"
#include "Object/GameObj/Base/ObjectManager.h"
#include "Object/GameObj/Base/GameObject.h"
#include "Object/GameObj/Player_Weapon.h"
#include "Object/GameObj/Player.h"
#include "Object/GameObj/Monster_Flower.h"
#include "Object/GameObj/Monster_BossFlower.h"
#include "Object/GameObj/Blooding.h"
#include "Object/GameObj/Gold.h"
#include "Object/GameObj/Item.h"
#include "Object/GameObj/Base/UIStateManager.h"

// Program
#include "Scene/Scene.h"
#include "Program/Program.h"

extern Vector2 mousePos;