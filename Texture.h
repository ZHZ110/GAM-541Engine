#pragma once
#include "pch.h"
#include "Renderer.h"

class Renderer;

class Texture {
public:
	Texture(ID3D11ShaderResourceView* texture_ptr);
	void bindTexture2D(Renderer* renderer);
private:
	ID3D11ShaderResourceView* m_texture_view = NULL;
};