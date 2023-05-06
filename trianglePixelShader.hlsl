struct Input {
	float4 position : SV_POSITION;
	float3 color: COLOR;
};

// go to the render target
float4 main(Input input) : SV_TARGET
{
	return float4(input.color.r, input.color.g, input.color.b, 1.0f);
}