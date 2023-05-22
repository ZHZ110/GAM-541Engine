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
	float2 rc: ROW_COL;
};

// go to the render target
float4 main(Input input) : SV_TARGET
{
	//return float4(input.tc.xy,0,1);
	//input.tc.x += (1/input.rc.x);
	input.tc.x += (1/input.rc.x);
	return tex.Sample(samAnisotropic,input.tc);
	//return float4(input.color.r, input.color.g, input.color.b, 1.0f);
}