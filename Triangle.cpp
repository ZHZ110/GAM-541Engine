#include "Triangle.h"
#include <fstream>
#include <vector>
#include "Renderer.h"
using namespace std;

struct Vertex {
	float x, y;
	float r, g, b;
};

Triangle::Triangle() {
	
}

Triangle::~Triangle() {
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
}

void Triangle::Initialize(Renderer* renderer) {
	createMesh(renderer);
	createShaders(renderer);
}

void Triangle::Draw(Renderer* renderer) {
	auto deviceContext = renderer->getDeviceContext();
	// Bind our triangle shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	// Bind our vertex buffer
	UINT stride = sizeof(Vertex); // how much to move in memory
	UINT offset = 0;
	// because we render stuff here, and we want to set the vertex buffer
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset); 

	// draw
	deviceContext->Draw(3, 0);
}

void Triangle::createMesh(Renderer* renderer) {
	// Define our vertices
	// first two are 2d coords, last three are rgb color, in cpu memory
	Vertex vertices[] = {
		{-1, -1, 1, 0, 0},
		{0, 1, 0, 1, 0},
		{1, -1, 0, 0, 1},
	};
	// create our vertex buffer, so that the video card can acess the vertices much quicker
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 }; //?
	vertexData.pSysMem = vertices; //?  

	renderer->getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	// check for errors here
}

void Triangle::createShaders(Renderer* renderer) {
	// create shaders
	ifstream vsFile("triangleVertexShader.cso", ios::binary);
	ifstream psFile("trianglePixelShader.cso", ios::binary);

	// read what's in the file byte by byte and put it in data
	vector<char> vsData = {istreambuf_iterator<char>(vsFile), istreambuf_iterator<char>()};
	vector<char> psData = {istreambuf_iterator<char>(psFile), istreambuf_iterator<char>()};

	// create resource
	renderer->getDevice()->CreateVertexShader(vsData.data(), vsData.size(), NULL, &m_vertexShader);
	renderer->getDevice()->CreatePixelShader(psData.data(), psData.size(), NULL, &m_pixelShader);

	// create input layouts: bridge between data to vertex shader
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR", 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	renderer->getDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}