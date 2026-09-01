// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

Vector2 mousePos;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 렌더링파이프 라인
// 책... device
// swapchain
// 

// CPU에서 그래픽스 작업이 비효율적이라 GPU에게 외주를 맡긴다.

//ID3D11Device* device;   // 컴퓨터 하드웨어 기능 지원 점검, 리소스 할당
//ID3D11DeviceContext* deviceContext; // 렌더링 대상 설정
// 리소스를 렌더링 파이프라인에 바인딩, GPU가 수행할 렌더링 명령 지시

//IDXGISwapChain* swapChain;
// 백버퍼
// DX의 인터페이스로써 1개 혹은 그 이상의 표면을 포함한다. (우리는 후면, 전면... 2개의 버퍼를 활용)
// 각각의 표면은 출력하기 전에 정보를 보관한다.
// 캐러비안의 해적... 해군들이 총 쏠 때 생각

//ID3D11RenderTargetView* renderTargetView; // 후면 버퍼 메모리
//
//ID3D11InputLayout* inputLayout;
//ID3D11VertexShader* vertexShader;
//ID3D11PixelShader* pixelShader;
//ID3D11Buffer* vertexBuffer;
//
//ID3D11ShaderResourceView* shaderResourceView;
//ID3D11SamplerState* samplerState;

// 과제 아래 내용, 역할 조사해오기
// 
// Device, DeviceContext 는 물리적인 그래픽 장치 하드웨어에 대한 소프트웨어 제어기라고 생각하면 된다.
//ID3D11Device* device; // 컴퓨터 하드웨어 기능 지원 점검, 리소스 할당
//ID3D11DeviceContext* deviceContext; //렌더 대상을 설정하고, 자원을 그래픽 파이프 라인에 묶고, GPU가 수행할 렌더링 명령들을 지시하는 데 쓰인다.
//// 리소스를 그래픽 파이프라인에 바인딩, GPU가 수행할 렌더링 명령 지시
//
//IDXGISwapChain* swapChain;
//// 백버퍼...
//// DX의 인터페이스로써 1개 혹은 그 이상의 표면을 표함한다.
//// 각각의 표면은 출력하기 전에 정보를 보관한다.
//// 캐러비안의 해적... 해군들이 총 쏠 때 생각
//   Swapchain이 없다면 모니터에 한 화면을 표현하려 할 때마다 시간이 걸려 '화면 깜빡임' 또는 '화면 찢어짐' 현상이 일어나게 된다.
// 
//   자원뷰: 자원을 파이프라인에 묶기 위해 사용하는 객체
//ID3D11RenderTargetView* renderTargetView; // 렌더타겟뷰: 2D텍스처등의 출력할 대상을 연결하는 자원 뷰, 여기서는 BackBuffer와 연결되어 BackBuffer에 그려진 대상들을 모니터로 출력해준다.
// 
//
//ID3D11InputLayout* inputLayout; // GPU에다가 버텍스 구조체의 레이아웃(VertexLayouts.h 등)을 설명하는 D3D 오브젝트
//ID3D11VertexShader* vertexShader; // 오브젝트의 Vertex의 정보(좌표, 색상, 텍스처, 조명 정보 등)를 토대로 오브젝트에 특별효과를 주는 쉐이더
//ID3D11PixelShader* pixelShader; // 렌더링 될 각각의 Pixel들을 계산하는 쉐이더
//ID3D11Buffer* vertexBuffer; // 버텍스들의 정보를 저장하는 버퍼
//
//ID3D11ShaderResourceView* shaderResourceView; // HLSL등의 프로그래밍이 가능한 셰이더 단계에서 PS, VS등에서 사용되는 자원을 연결하는 뷰
//ID3D11SamplerState* samplerState; // 텍스처의 픽셀을 읽어들일때 필터링 및 샘플링처리를 위해 사용하는 변수. 읽어들일 텍스처픽셀의 가공에 대한 주문내용이 담겨져있다.
// + IndexBuffer    // 버텍스의 렌더링순서를 저장하는 버퍼
// + ConstantBuffer // VS(버텍스셰이더) 또는 PS(픽셀셰이더)에서 사용될 상수를 모아 놓은 버퍼
// + SRT // Scale * Rotation * Translation

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg = {};

    // Main message loop:
    // 생성
    Device::Create(hWnd);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DEVICE_CONTEXT);

    StateManager::Create();
    ShaderManager::Create();
    EffectManager::Create();
    Camera::Create();
    DirectWrite::Create();

    shared_ptr<Program> program = make_shared<Program>();

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 할일
            program->Update();
            program->Render();
        }
    }

    // 삭제
    DirectWrite::Delete();
    Camera::Delete();
    EffectManager::Delete();
    ShaderManager::Delete();
    StateManager::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    Device::Delete();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rc = { 0,0,WINWIDTH,WINHEIGHT };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       WINSTARTX, WINSTARTY, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

   SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
    {
        mousePos.x = static_cast<float>(LOWORD(lParam));
        mousePos.y = WINHEIGHT - static_cast<float>(HIWORD(lParam));
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//void InitDevice()
//{
//    RECT rc;
//    GetClientRect(hWnd, &rc);
//    UINT width = rc.right - rc.left;
//    UINT height = rc.bottom - rc.top;
//
//    D3D_FEATURE_LEVEL featureLevels[] =
//    {
//        D3D_FEATURE_LEVEL_11_0,
//        D3D_FEATURE_LEVEL_10_1,
//        D3D_FEATURE_LEVEL_10_0,
//    };
//
//    UINT featureSize = ARRAYSIZE(featureLevels);
//
//    DXGI_SWAP_CHAIN_DESC sd = {};
//    sd.BufferCount = 1; // 후면버퍼 갯수
//    sd.BufferDesc.Width = width;
//    sd.BufferDesc.Height = height;
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferDesc.RefreshRate.Numerator = 60;
//    sd.BufferDesc.RefreshRate.Denominator = 1;
//    // 디스플레이 주사율 (Numerator / Denominator)
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //위에 버퍼를 백버퍼로 쓰겠다.
//    sd.OutputWindow = hWnd;
//    sd.SampleDesc.Count = 1;
//    sd.SampleDesc.Quality = 0;
//    sd.Windowed = true;
//
//    D3D11CreateDeviceAndSwapChain
//    (
//        nullptr,
//        D3D_DRIVER_TYPE_HARDWARE,
//        0,
//        D3D11_CREATE_DEVICE_DEBUG,
//        featureLevels,
//        featureSize,
//        D3D11_SDK_VERSION,
//        &sd,
//        &swapChain,
//        &device,
//        nullptr,
//        &deviceContext
//    );
//
//    ID3D11Texture2D* backBuffer;
//
//    // void*
//    // 모든 자료형을 다 받을 수 있다.
//    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
//    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
//    backBuffer->Release();
//
//    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
//
//    //////////////////////////
//    D3D11_VIEWPORT vp;
//    vp.Width = width;
//    vp.Height = height;
//    vp.MinDepth = 0.0f;
//    vp.MaxDepth = 1.0f;
//    vp.TopLeftX = 0;
//    vp.TopLeftY = 0;
//    deviceContext->RSSetViewports(1, &vp);
//
//    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
//
//    ID3D10Blob* vertexBlob;
//    D3DCompileFromFile(L"Shaders/Tutorial.hlsl", nullptr, nullptr, "VS",
//        "vs_5_0", flags, 0, &vertexBlob, nullptr);
//
//    device->CreateVertexShader(vertexBlob->GetBufferPointer(),
//        vertexBlob->GetBufferSize(), nullptr, &vertexShader);
//
//    D3D11_INPUT_ELEMENT_DESC layout[] =
//    {
//        {
//            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
//            D3D11_INPUT_PER_VERTEX_DATA,0
//        },
//        {
//            "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
//            D3D11_INPUT_PER_VERTEX_DATA,0
//        }
//    };
//
//    UINT layoutSize = ARRAYSIZE(layout);
//
//    device->CreateInputLayout(layout, layoutSize, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
//        &inputLayout);
//
//    vertexBlob->Release();
//
//    ID3DBlob* pixelBlob;
//    D3DCompileFromFile(L"Shaders/Tutorial.hlsl", nullptr, nullptr, "PS", "ps_5_0", flags, 0, &pixelBlob, nullptr);
//
//    device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, &pixelShader);
//
//    //pixelBlob->Release();
//
//    // Polygon : 정점 3개로 이루어진 3D공간에서의 삼각형
//    // 시계방향을 앞방향으로 해서 앞쪽에서만 보임.
//
//    /*
//    Vertex vertices[] =
//    {
//        XMFLOAT3(0.0f, 0.5f, 0.0f),
//        XMFLOAT3(0.5f, -0.5f, 0.0f),
//        XMFLOAT3(-0.5f, -0.5f, 0.0f)
//    };
//    */
//
//    vector<Vertex> vertices;
//
//    Vertex v;
//    v.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
//    v.uv = { 0, 0 };
//    vertices.emplace_back(v);
//
//    v.pos = XMFLOAT3(0.5f, 0.5f, 0.0f);
//    v.uv = { 1.0f, 0 };
//    vertices.emplace_back(v);
//
//    v.pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);
//    v.uv = { 0, 1.0f };
//    vertices.emplace_back(v);
//
//    v.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
//    v.uv = { 1.0f, 1.0f };
//    vertices.emplace_back(v);
//
//    //v.pos = XMFLOAT3()
//
//    D3D11_BUFFER_DESC bd = {};
//    bd.Usage = D3D11_USAGE_DEFAULT;
//    bd.ByteWidth = sizeof(Vertex) * vertices.size();
//    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//    D3D11_SUBRESOURCE_DATA initData = {};
//    initData.pSysMem = &vertices[0];
//
//    device->CreateBuffer(&bd, &initData, &vertexBuffer);
//
//    ScratchImage image;
//    LoadFromWICFile(L"Resource/Textures/eldenring.png", WIC_FLAGS_NONE, nullptr, image);
//    
//    CreateShaderResourceView(device, image.GetImages(), image.GetImageCount(),
//        image.GetMetadata(), &shaderResourceView);
//
//    D3D11_SAMPLER_DESC sampDesc = {};
//    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
//    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
//    sampDesc.MaxLOD = 0;
//    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
//
//    device->CreateSamplerState(&sampDesc, &samplerState);
//}
//
//void Render()
//{
//    //FLOAT myColorR = 184.0f / 255.0f;
//    //FLOAT myColorG = 223.0f / 255.0f;
//    //FLOAT myColorB = 248.0f / 255.0f;
//    //FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f};
//    FLOAT clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
//
//    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
//
//    UINT stride = sizeof(Vertex);
//    UINT offset = 0;
//
//    deviceContext->IASetInputLayout(inputLayout);
//
//    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
//    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//    deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
//    deviceContext->PSSetSamplers(0, 1, &samplerState);
//
//    deviceContext->VSSetShader(vertexShader, nullptr, 0);
//    deviceContext->PSSetShader(pixelShader, nullptr, 0);
//
//    deviceContext->Draw(4, 0);
//
//    swapChain->Present(0, 0);
//}
//
//void ReleaseDevice()
//{
//    device->Release();
//    deviceContext->Release();
//    swapChain->Release();
//    renderTargetView->Release();
//
//    vertexShader->Release();
//    pixelShader->Release();
//    inputLayout->Release();
//    vertexBuffer->Release();
//
//    shaderResourceView->Release();
//    samplerState->Release();
//}