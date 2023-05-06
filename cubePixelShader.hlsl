Texture2D tex;
SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct Input {
	float2 tc : TEXCOORD;
	float3 color: COLOR;
	float4 position : SV_POSITION;
};

// go to the render target
float4 main(Input input) : SV_TARGET
{
	//return float4(input.tc.xy,0,1);
	return tex.Sample(samAnisotropic,input.tc);
	//return float4(input.color.r, input.color.g, input.color.b, 1.0f);
}