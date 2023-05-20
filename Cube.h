#pragma once
#include "d3dx11effect.h"
#include "Camera.h"
namespace dx = DirectX;

class Renderer;
class Texture;
class Sampler;
class Sprite;

struct model_view_proj {
	dx::XMFLOAT4X4 model;
	dx::XMFLOAT4X4 view;
	dx::XMFLOAT4X4 proj;

};

class Cube {
public:
	Cube();
	~Cube();
	void Initialize(Renderer* renderer);
	void Draw(Renderer* renderer, Sprite* sprite, Texture* texture, float dt);
private:
	void createMesh(Renderer* renderer);
	void createShaders(Renderer* renderer);
	void createVertexBuffer(Renderer* renderer);
	void createIndexBuffer(Renderer* renderer);
	void createConstantBuffer(Sprite* sprite, Renderer* renderer);

	ID3D11Buffer* m_cubeVB = NULL;
	ID3D11Buffer* m_cubeIB = NULL;
	ID3D11Buffer* m_constBuffer = NULL;
	Sampler* cube_sampler;
	ID3D11ShaderResourceView* m_texture_view = NULL;


	//ID3DX11Effect* mFX;
	//ID3DX11EffectTechnique* m_tech;
	//ID3DX11EffectMatrixVariable* m_fxWorldViewProj;
	model_view_proj world_view_proj;

	ID3D11VertexShader* m_vertexShader = NULL;
	ID3D11PixelShader* m_pixelShader = NULL;
	ID3D11InputLayout* m_inputLayout = NULL;
	float angle = 0;

};
