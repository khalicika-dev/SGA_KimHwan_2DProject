#pragma once
class Device
{
private:
	Device(HWND hWnd);
	~Device();
public:
	static void Create(HWND hWnd)
	{
		if (m_instance == nullptr)
			m_instance = new Device(hWnd);
	}

	static void Delete()
	{
		delete m_instance;
	}

	static Device* Get() 
	{
		if (m_instance != nullptr)
			return m_instance;

		return nullptr;
	}

	ID3D11Device* GetDevice() { return m_device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_deviceContext; }
	IDXGISwapChain* GetSwapChain() { return m_swapChain; }

	void SetRenderTarget();
	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	void Clear();
	void Present();
private:
	HWND m_hWnd;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_renderTargetView;

	static Device* m_instance;
};

