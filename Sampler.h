#pragma once

class Renderer;

class Sampler {
public:
	Sampler(Renderer* renderer);
	void Bind(Renderer* renderer);
private:
	ID3D11SamplerState* m_sampler;
};