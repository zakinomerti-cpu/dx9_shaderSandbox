// vs_3_0
float4 vs_main(float2 pos : POSITION) : POSITION {
	return float4(pos, 0.0f, 1.0f);
}

// ps_3_0
float4 ps_main() : COLOR0 {
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}
