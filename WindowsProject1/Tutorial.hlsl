
// SV : system value
//
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

// 후면버퍼
float4 PS() : SV_TARGET
{
	//             r    g    b    a
	return float4(0.0f,0.0f,0.0f,1.0f);
}