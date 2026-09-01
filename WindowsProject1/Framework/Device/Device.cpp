#include "Framework.h"
#include "Device.h"

Device* Device::m_instance = nullptr;

Device::Device(HWND hWnd)
	: m_hWnd(hWnd)
{
	CreateDeviceAndSwapChain();
	CreateBackBuffer();
}

Device::~Device()
{
	m_device->Release();
	m_deviceContext->Release();
	m_swapChain->Release();
	m_renderTargetView->Release();
}

void Device::SetRenderTarget()
{
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
}

void Device::CreateDeviceAndSwapChain()
{
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1; // 후면버퍼 갯수
    sd.BufferDesc.Width = WINWIDTH;
    sd.BufferDesc.Height = WINHEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // 디스플레이 주사율 (Numerator / Denominator)
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //위에 버퍼를 백버퍼로 쓰겠다.
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        &m_swapChain,
        &m_device,
        nullptr,
        &m_deviceContext
    );
}

void Device::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    // void*
    // 모든 자료형을 다 받을 수 있다.
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
    backBuffer->Release();

    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

    //////////////////////////
    D3D11_VIEWPORT vp;
    vp.Width = WINWIDTH;
    vp.Height = WINHEIGHT;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_deviceContext->RSSetViewports(1, &vp);
}

void Device::Clear()
{
    FLOAT clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}

void Device::Present()
{
    m_swapChain->Present(0, 0);
}