#pragma once
#include <vector>
#include <d3d11.h>
#include "ISystem.h"
#include "Window.h"
#include "Cube.h"
#include "Triangle.h"
#include "Camera.h"
#include "Sprite.h"
#include <map>

class Renderer : public ISystem{
public:
	Renderer(Window* window);
	void Initialize();
	void Update(float dt);
	void ShutDown();
	void getMessage(const Message* msg);
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	Camera* getCamera();
	void LoadTextures();
	void setTexture(const std::string& texture_name);
	void addSprite(Sprite* sprite);
private:
	// Device components
	IDXGISwapChain* m_SwapChain = NULL; // swap buffer at the end of frame
	ID3D11Device* m_device = NULL; // create resource
	ID3D11DeviceContext* m_deviceContext = NULL; // what you use to render stuff

	void createDevice(Window* window);
	void createRenderTarget();
	void beginFrame(); // initialize the buffer
	void endFrame(); // swap the buffer
	Texture* CreateTexture(const std::string& filepath);

	// Render Target
	Cube cube;
	Triangle triangle;
	Camera* camera;
	ID3D11RenderTargetView* m_RenderTargetView = NULL;
	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;
	D3D11_TEXTURE2D_DESC m_backBufferDesc;
	std::vector<Sprite*> spriteComponents;
	std::map<std::string, Texture*> texture_map;
	Texture* currTexture;
};