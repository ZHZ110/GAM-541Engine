#pragma once
#include "d3dx11effect.h"

class Renderer;

class Triangle {
public:
	Triangle();
	~Triangle();
	void Initialize(Renderer* renderer);
	void Draw(Renderer* renderer);
private:
	void createMesh(Renderer* renderer);
	void createShaders(Renderer* renderer);

	ID3D11Buffer* m_vertexBuffer = NULL;
	ID3D11VertexShader* m_vertexShader = NULL;
	ID3D11PixelShader* m_pixelShader = NULL;
	ID3D11InputLayout* m_inputLayout = NULL;
};
