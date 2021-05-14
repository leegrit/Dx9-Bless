texture RenderTargetTex;
sampler RenderTargetSampler = sampler_state
{
	texture = RenderTargetTex;
};

float4 DebugMRTPS(float2 texcoord : TEXCOORD0) : COLOR0
{
	return tex2D(RenderTargetSampler, texcoord);
};

technique DebugMRT
{
	pass P0
	{
		ZEnable = false;

		VertexShader = NULL;
		PixelShader = compile ps_3_0 DebugMRTPS();
	}
};
