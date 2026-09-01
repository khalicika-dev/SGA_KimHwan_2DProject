cbuffer Action : register(b0)
{
	float2 startPos;
	float2 size;
	float2 maxSize;
	float alpha;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
	float4 pos : SV_position;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	float4 result;
	float2 uv;
	uv = input.uv * (size / maxSize) + (startPos / maxSize);

	result =  map.Sample(samp, uv);
	result.a *= alpha;
	return result;
}