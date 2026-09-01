Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
	float4 pos : SV_position;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	////             r      g     b    a
	//return float4(0.2f, 0.7f, 0.0f, 1.0f);
	//return input.color;
	return map.Sample(samp,input.uv);
}