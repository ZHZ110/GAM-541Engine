#include "pch.h"
#include <fstream>
#include <vector>
#include "Renderer.h"
#include "Cube.h"
#include "d3d11.h"
#include "d3dx11Effect.h"
#include "GameObject.h"
#include "Texture.h"
#include "Sampler.h"
using namespace std;
namespace dx = DirectX;

struct Vertex {
	float x, y, z;
	float r, g, b;
	float u, v;
};

struct const_buffer_struct {
	dx::XMFLOAT4X4 model;
	dx::XMFLOAT4X4 view;
	dx::XMFLOAT4X4 proj;
	int numRow;
	int numCol;
	int currentFrame;
	int endFrame;
};

Cube::Cube() {
}

Cube::~Cube() {
	m_cubeVB->Release();
	m_cubeIB->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
	//delete cube_texture;
	delete cube_sampler;
	//mFX->Release();
}

void Cube::Initialize(Renderer* renderer) {
	createMesh(renderer);
	createShaders(renderer);
	//cube_texture = new Texture(renderer);
	cube_sampler = new Sampler(renderer);
	cube_sampler->Bind(renderer);
}

void Cube::Draw(Renderer* renderer, Sprite* sprite, Texture* texture, float dt) {
	auto deviceContext = renderer->getDeviceContext();
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Bind vertex and pixel shaders
 	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	//deviceContext->VSSetConstantBuffers(0, 1, &m_constBuffer);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	// Bind Vertex buffer and index buffer
	UINT stride = sizeof(Vertex);  // how much to move in memory
	UINT offset = 0;
	// because we render stuff here, and we want to set the vertex buffer
	deviceContext->IASetVertexBuffers(0, 1, &m_cubeVB, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_cubeIB, DXGI_FORMAT_R32_UINT, 0);

	createConstantBuffer(sprite, renderer);
	// need to bind the constant buffer to vertex shader
	deviceContext->VSSetConstantBuffers(0, 1, &m_constBuffer);

	texture->bindTexture2D(renderer);

	deviceContext->DrawIndexed(36, 0, 0);
}

void Cube::createMesh(Renderer* renderer) {
	createVertexBuffer(renderer);
	createIndexBuffer(renderer);
}

void Cube::createVertexBuffer(Renderer* renderer) {
	// create vertex buffer
	// Define vertices for the cube directly
	// keep the ones with negative z later
	Vertex vertices[] = {
		{ -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		{ -1.0f, -1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
		{ -1.0f, +1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
		//{ +1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		//{ +1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
		//{ +1.0f, +1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
		//{ +1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }
	};
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;  
	vbd.ByteWidth = sizeof(Vertex) * 4; // 8 bytes?
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	renderer->getDevice()->CreateBuffer(&vbd, &vinitData, &m_cubeVB);
}

void Cube::createIndexBuffer(Renderer* renderer) {
	// create index buffer
	UINT indices[] = {
		    0,2,1, // -x
			1,2,3,

			//4,5,6, // +x
			//5,7,6,
			//
			//0,1,5, // -y
			//0,5,4,
			//
			//2,6,7, // +y
			//2,7,3,
			//
			//0,4,6, // -z
			//0,6,2,
			//
			//1,3,7, // +z
			//1,7,5,
	};
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof(UINT) * 6;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	renderer->getDevice()->CreateBuffer(&ibd, &iinitData, &m_cubeIB);
	//renderer->getDeviceContext()->IASetIndexBuffer(m_cubeIB, DXGI_FORMAT_R32_UINT, 0);
	//renderer->getDevice()->SetStreamSource(0, m_cubeVB, 0, sizeof(Vertex));
	//renderer->getDevice()->SetIndices(m_cubeIB);
}

inline dx::XMMATRIX XM_CALLCONV XMIdentityMatrix() 
{
	return dx::XMMATRIX(1.0f, 0.0f, 0.0f, 0.0f,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

void Cube::createConstantBuffer(Sprite* sprite, Renderer* renderer) {
	XMMATRIX T = dx::XMMatrixTranslationFromVector(sprite->getParent()->getTranslate());
	renderer->getCamera()->UpdateViewMatrix();
	dx::XMMATRIX scale_matrix = dx::XMMatrixScalingFromVector(sprite->getParent()->getScale());
	dx::XMMATRIX rotation_matrix = dx::XMMatrixRotationX(dx::XM_PI / 2);
	dx::XMMATRIX position = scale_matrix * rotation_matrix * dx::XMMatrixRotationY(dx::XM_PI/2) * dx::XMMatrixTranslationFromVector(sprite->getParent()->getTranslate());
	position = dx::XMMatrixTranspose(position);
	//dx::XMStoreFloat4x4(&world_view_proj.model, dx::XMMatrixTranslationFromVector(sprite->getParent()->getTranslate()));
	const_buffer_struct cbuffer_struct;
	dx::XMStoreFloat4x4(&cbuffer_struct.model, position);
	dx::XMStoreFloat4x4(&cbuffer_struct.view, renderer->getCamera()->View()); // the camera
	dx::XMStoreFloat4x4(&cbuffer_struct.proj, renderer->getCamera()->Proj()); // rotation
	cbuffer_struct.numCol = sprite->getCols();
	cbuffer_struct.numRow = sprite->getRows();
	cbuffer_struct.currentFrame = sprite->getCurrFrame();
	//if (cbuffer_struct.currentFrame > 0) {
		//printf("current Frame over 0\n");
	//}
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cbuffer_struct);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA cinitData = {};
	cinitData.pSysMem = &cbuffer_struct;
	renderer->getDevice()->CreateBuffer(&cbd, &cinitData, &m_constBuffer);
}

void Cube::createShaders(Renderer* renderer) {
	// create shaders
	ifstream vsFile("cubeVertexShader.cso", ios::binary);
	ifstream psFile("cubePixelShader.cso", ios::binary);
	// read what's in the file byte by byte and put it in data
	vector<char> vsData = { istreambuf_iterator<char>(vsFile), istreambuf_iterator<char>() };
	vector<char> psData = { istreambuf_iterator<char>(psFile), istreambuf_iterator<char>() };
	// create resource
	renderer->getDevice()->CreateVertexShader(vsData.data(), vsData.size(), NULL, &m_vertexShader);
	renderer->getDevice()->CreatePixelShader(psData.data(), psData.size(), NULL, &m_pixelShader);
	// create input layouts: bridge between data to vertex shader
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR", 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	renderer->getDevice()->CreateInputLayout(layout, 3, vsData.data(), vsData.size(), &m_inputLayout);

}
