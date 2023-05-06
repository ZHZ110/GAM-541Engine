#include "pch.h"
#include "Sampler.h"
#include "Renderer.h"

Sampler::Sampler(Renderer* renderer) {

	HRESULT hr = S_OK;
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//hr = renderer->getDevice()->CreateSamplerState(&samplerDesc, &m_sampler);
	hr = S_OK;
}

void Sampler::Bind(Renderer* renderer) {
	//renderer->getDeviceContext()->PSSetSamplers(0, 1, &m_sampler);
}