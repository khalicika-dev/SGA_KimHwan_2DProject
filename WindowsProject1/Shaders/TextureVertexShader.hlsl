// SV : system value
cbuffer World : register(b0)
{
	matrix world;
}

cbuffer View : register(b1)
{
	matrix view;
}

cbuffer Projection : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

struct VertexOutput
{
	float4 pos : SV_position;
	float2 uv : UV;
};

// 1프레임당 호출 횟수?
// 정점 4개

// 시멘틱 변수가 어떤 역할 하는지 지칭
VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.pos = mul(input.pos,world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;

	return output;
}