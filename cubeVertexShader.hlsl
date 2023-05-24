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
	float2 offset: OffSet;
};

cbuffer cbPerObject
{
	float4x4 model;
	float4x4 view;
	float4x4 projection;
	int numRow;
	int numCol;
	int currentFrame;
	int endFrame;
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
	vso.tex.x = tex.x/numCol;
	vso.tex.y = tex.y/numRow;
	vso.offset.x = (1.0f / numCol) * (currentFrame % numCol);
	vso.offset.y = (1.0f / numRow) * (int)(currentFrame / numCol);
	return vso;
}