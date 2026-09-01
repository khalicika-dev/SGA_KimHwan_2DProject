#pragma once
using namespace DirectX;

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define WINSTARTX 0
#define WINSTARTY 0
#define WINWIDTH 800
#define WINHEIGHT 400
#define CENTER_X WINWIDTH*0.5f
#define CENTER_Y WINHEIGHT*0.5f

#define PI 3.141592
#define FRAME 1/60

#define LERP(s,e,t) (s + (e - s) * t)

class Device;
#define DEVICE Device::Get()->GetDevice()
#define DEVICE_CONTEXT Device::Get()->GetDeviceContext()

class Keyboard;
#define CREATE_KEYBOARD() Keyboard::Create()
#define GET_KEYBOARD Keyboard::Get()
#define KEYDOWN(k) GET_KEYBOARD->Down(k)
#define KEYPRESS(k) GET_KEYBOARD->Press(k)
#define KEYUP(k) GET_KEYBOARD->Up(k)
#define DELETE_KEYBOARD() Keyboard::Delete()

class Timer;
#define CREATE_TIMER() Timer::Create()
#define GET_TIMER Timer::Get()
#define DELTATIME Timer::Get()->GetElapsedTime()
#define DELETE_TIMER() Timer::Delete()

class Debugger;
#define CREATE_DEBUGGER() Debugger::Create()
#define DEBUG Debugger::Get()
#define DELETE_DEBUGGER() Debugger::Delete()

class StateManager;
#define SAMPLER StateManager::Get()->GetSampler()
#define AlphaBlendState StateManager::Get()->GetAlphaBlend()
#define AdditiveBlendState StateManager::Get()->GetAdditiveBlend()
#define CullModeState StateManager::Get()->GetCullMode()

class ShaderManager;
#define SHADER ShaderManager::Get()

class EffectManager;
#define EFFECT EffectManager::Get()

class Camera;
#define CAMERA Camera::GetInstance()

class MapManager;
#define MAPMANAGER MapManager::Get()
#define MAP MapManager::MAPLIST

class ObjectManager;
#define OBJECT ObjectManager::Get()
#define OBJTYPE ObjectManager::ObjectType
#define PTCTYPE ObjectManager::ParticleType
#define PREPARE_PLAYER() ObjectManager::Get()->Prepare(ObjectManager::ObjectType::PLAYER, 0)
#define GET_PLAYER ObjectManager::Get()->FindPlayer()

class UIStateManager;
#define UISTATE UIStateManager::Get()
#define UI_UPDATE() UIStateManager::Get()->Update()
#define UI_RENDER() UIStateManager::Get()->Render()

// assert
#define V(hr) assert(SUCCEEDED(hr))


// 콜백함수 TypeDef
//using Delegate = void(*)(void);
typedef function<void()> Delegate;

typedef XMFLOAT2	Float2;
typedef XMFLOAT3	Float3;
typedef XMFLOAT4	Float4;
typedef XMMATRIX	Matrix;
typedef XMFLOAT4X4	Float4x4;