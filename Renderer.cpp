#include "Renderer.h"
#include "GameObject.h"
#include "Triangle.h"
#include "Cube.h"
#include "Texture.h"
#include "WICTextureLoader.h"

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
			setTexture(spriteComponents[i]);
			cube.Draw(this, spriteComponents[i], currTexture, dt);
			spriteComponents[i]->frameUpdate(dt);
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
	const std::string spaceship_name = "spaceship";
	const std::string enemy_name = "enemy";
	const std::string bullet_name = "bullet";
	const std::string file_path = "Assets/Textures/";
	std::string spaceship_path = "Assets/Textures/spaceship.png";
	std::string enemy_path = "Assets/Textures/enemy.png";
	std::string bullet_path = "Assets/Textures/bullet.png";
	texture_map["spaceship"] = CreateTexture(spaceship_path);
	texture_map["enemy"] = CreateTexture(enemy_path);
	texture_map["bullet"] = CreateTexture(bullet_path);
	//spriteComponents[0]->textureName = spaceship_name;
	spriteComponents[0]->setRows(2);
	spriteComponents[0]->setCols(4);
	spriteComponents[0]->setTotalFrames(8);
	spriteComponents[1]->setRows(2);
	spriteComponents[1]->setCols(4);
	spriteComponents[1]->setTotalFrames(8);
	for (int i = 2; i < spriteComponents.size(); ++i) {
		spriteComponents[i]->setRows(1);
		spriteComponents[i]->setCols(1);
		spriteComponents[i]->setTotalFrames(1);
	}
}

void Renderer::setTexture(Sprite* spriteComponent) {
	currTexture = texture_map[spriteComponent->textureName];
	spriteComponent->setSpriteSource(currTexture);
}

Texture* Renderer::CreateTexture(const std::string& filepath) {
	HRESULT hr = S_OK;

	std::wstring tempStr = std::wstring(filepath.begin(), filepath.end());
	LPCWSTR wideString = tempStr.c_str();

	ID3D11ShaderResourceView* mDiffuseMapSRV = nullptr;
	hr = DirectX::CreateWICTextureFromFile(m_device, m_deviceContext, tempStr.c_str(), nullptr, &mDiffuseMapSRV, 0);
	return new Texture(mDiffuseMapSRV);
}
