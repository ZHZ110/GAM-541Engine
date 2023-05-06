/*cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
};
void main(float3 iPosL : POSITION,
	float4 iColor : COLOR,
	out float4 oPosH : SV_POSITION,
	out float4 oColor : COLOR)
{
	// Transform to homogeneous clip space.
	oPosH = mul(float4(iPosL, 1.0f), gWorldViewProj);
	// Just pass vertex color into the pixel shader.
	oColor = iColor;
}*/

struct VSOut {
	float2 tex : TexCoord;
	float3 color : Color;
	float4 pos: SV_Position;
};

cbuffer cbPerObject
{
	float4x4 model;
	float4x4 view;
	float4x4 projection;
	//float4x4 gWorldInvTranspose;
	//float4x4 gWorldViewProj;
	//Material gMaterial;
};

VSOut main(float3 position : Position, float3 color : Color, float2 tex:TexCoord) {
	VSOut vso;
	//vso.pos = mul(float4(pos, 1.0f), cbPerObject);
	float4 pos = float4(position, 1.0f);
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	vso.pos = pos;
	vso.color = color;
	vso.tex = tex;
	return vso;
}