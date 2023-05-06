#include "Texture.h"
#include "Renderer.h"

Texture::Texture(ID3D11Texture2D* texture_ptr, Renderer* renderer) {
	m_texture = texture_ptr;
	createTexture2D(renderer);
	bindTexture2D(renderer);
}

void Texture::createTexture2D(Renderer* renderer) {
	HRESULT res = S_OK;

	// need to create the resource view on the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;
	res = renderer->getDevice()->CreateShaderResourceView(m_texture, &srvd, &m_texture_view);
}

void Texture::bindTexture2D(Renderer* renderer) {
	ID3D11ShaderResourceView* srv[1] = { m_texture_view };
	renderer->getDeviceContext()->PSSetShaderResources(0u, 1u, srv);
}