#include "Renderer.h"
#include "GameObject.h"
#include "Triangle.h"
#include "Cube.h"
#include "Texture.h"

Renderer* RENDERER = nullptr;

Renderer::Renderer(Window* window) {
	RENDERER = this;
	Renderer::createDevice(window);
}

void Renderer::Initialize()
{
	Renderer::createRenderTarget();
	camera = new Camera();
	cube.Initialize(this);
	//LoadTextures();
	//triangle.Initialize(this);
}

void Renderer::Update(float dt) 
{
	for (int i = 0; i < spriteComponents.size(); ++i) {
		if (spriteComponents[i] != NULL && !spriteComponents[i]->getParent()->getActive()) {
			spriteComponents[i] = nullptr;
		}
	}

	Renderer::beginFrame(); // initialize the buffer


	for (int i = 0; i < spriteComponents.size(); ++i) {
		if (spriteComponents[i] != NULL && spriteComponents[i]->getParent()->getRender() == true) {
			//auto texture = texture_map[spriteComponents[i]->textureName];
			//auto texture = texture_map["darkbrick"];
			setTexture(spriteComponents[i]->textureName);
			cube.Draw(this, spriteComponents[i], currTexture, dt);
		}
	}
	//triangle.Draw(this);

	Renderer::endFrame(); // swap the buffer// Draw loop
}

void Renderer::ShutDown() {
	RENDERER = nullptr;
	delete camera;
}

void Renderer::getMessage(const Message* msg) {
	dx::XMFLOAT2 upRight;
	float frontBack; // front:positive; back:negative
	// move the camera here
	switch (msg->getType()) {
	case MessageType::CAMERA_STRAFE:
		upRight = reinterpret_cast<const CameraStrafing*>(msg)->move_xy;
		camera->CameraStrafe(upRight);
		break;
	case MessageType::CAMERA_MOVE_FRONT_BACK:
		frontBack = reinterpret_cast<const CameraMoveFrontBack*>(msg)->front_back_move;
		camera->MoveCameraFrontBack(frontBack);
		break;
	}
}

Camera* Renderer::getCamera() {
	return camera;
}

void Renderer::addSprite(Sprite* sprite) {
	for (int i = 0; i < spriteComponents.size(); ++i) {
		if (spriteComponents[i] == NULL) {
			spriteComponents[i] = sprite;
			return;
		}
	}

	spriteComponents.push_back(sprite);
}

void Renderer::createDevice(Window* window) {
	// define swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window->getHandle();
	swapChainDesc.SampleDesc.Count = 1; // multi-sampling
	swapChainDesc.Windowed = true; // so that it's not full screen ( can change that later)

	// Create the swap chain device and device context
	auto result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0,
		NULL, 0, D3D11_SDK_VERSION, &swapChainDesc,
		&m_SwapChain, &m_device, NULL, &m_deviceContext);

	// Error(result != S_OK, "Problem creating DX11SwapChain");
	// Warning(texture == nullptr, "Texture not found")
	// Info(result == S_OK, "Device created successfully");
	
	// Check for errors of the above function
	if (result != S_OK) {
		MessageBox(NULL, "Problem creating DX11SwapChain", "Error", MB_OK);
		exit(0);
	}
}

void Renderer::createRenderTarget() {
	ID3D11Texture2D* backBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView);
	backBuffer->GetDesc(&m_backBufferDesc);
	backBuffer->Release();
}

void Renderer::beginFrame() {
	//Bind render target
	m_deviceContext->OMSetRenderTargets(1, &m_RenderTargetView, NULL);
	// Set the viewport
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, 800.f, 600.f);
	m_deviceContext->RSSetViewports(1, &viewport);
	// Set the background color
	float clearColor[] = { 0.25f, 0.5f, 1, 1 };
	m_deviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor); // This is actually the rendering step
}

void Renderer::endFrame() {
	// swap the buffer
	m_SwapChain->Present(1, 0); // 1 means it's vsynced
}

ID3D11Device* Renderer::getDevice() {
	return m_device;
}

ID3D11DeviceContext* Renderer::getDeviceContext() {
	return m_deviceContext;
}

void Renderer::LoadTextures() {
	std::string spaceship_path = "Assets/Textures/spaceship.png";
	std::string enemy_path = "Assets/Textures/enemy.png";
	std::string bullet_path = "Assets/Textures/bullet.png";
	texture_map["spaceship"] = CreateTexture(spaceship_path);
	texture_map["enemy"] = CreateTexture(enemy_path);
	texture_map["bullet"] = CreateTexture(bullet_path);
	//spriteComponents[0]->textureName = "sapceship";
	//spriteComponents[1]->textureName = "enemy";
	//spriteComponents[2]->textureName = "bullet";
}

void Renderer::setTexture(const std::string& texture_name) {
	currTexture = texture_map[texture_name];
}

Texture* Renderer::CreateTexture(const std::string& filepath) {
	HRESULT hr = S_OK;

	// Initialization0
	IWICImagingFactory* factory;
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

	IWICBitmapDecoder* pIDecoder = NULL;
	IWICBitmapFrameDecode* pIDecoderFrame = NULL;

	// Every time you want to load a texture
	std::wstring tempStr = std::wstring(filepath.begin(), filepath.end());
	LPCWSTR wideString = tempStr.c_str();
	hr = factory->CreateDecoderFromFilename(wideString, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pIDecoder);
	hr = pIDecoder->GetFrame(0, &pIDecoderFrame);
	UINT width, height;
	hr = pIDecoderFrame->GetSize(&width, &height);

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	UINT bytesPerPixel = 4;
	UINT stride = width * bytesPerPixel;
	UINT size = width * height * 4;
	BYTE* temp = new BYTE[size];
	hr = pIDecoderFrame->CopyPixels(nullptr, stride, size, temp);
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = temp;
	data.SysMemPitch = width;
	data.SysMemSlicePitch = size;

	ID3D11Texture2D* texture = nullptr;
	hr =getDevice()->CreateTexture2D(&desc, &data, &texture);

	return new Texture(texture, this);
}
