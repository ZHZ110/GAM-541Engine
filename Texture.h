#pragma once
#include "pch.h"
#include "Renderer.h"

class Renderer;

class Texture {
public:
	Texture(ID3D11Texture2D* texture_ptr, Renderer* renderer);
	void bindTexture2D(Renderer* renderer);
	ID3D11Texture2D* m_texture = NULL;
private:
	void createTexture2D(Renderer* renderer);
	//ID3D11Texture2D* m_texture = NULL;
	ID3D11ShaderResourceView* m_texture_view = NULL;
};