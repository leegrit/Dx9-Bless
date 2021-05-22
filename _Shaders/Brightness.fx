
texture ScreenTex;
sampler ScreenSampler = sampler_state
{
	texture = ScreenTex;
};

texture EffectMaskTex;
sampler EffectMaskSampler = sampler_state
{
	texture = EffectMaskTex;
};

struct PixelOutput
{
	float4 color : COLOR0; // brightness surface
};



PixelOutput BrightnessPS(float2 texcoord : TEXCOORD0)
{
	PixelOutput output = (PixelOutput)0;

	float4 screen = tex2D(ScreenSampler, texcoord);
	float4 effectMask = tex2D(EffectMaskSampler, texcoord);

	output.color = screen * effectMask.g;
	float brightness = dot(screen.rgb, float3(0.2126f, 0.7152f, 0.0722f));
	if(brightness > 0.99)
		output.color = screen;

	return output;
};


technique Brightness
{
	pass P0
	{
		ZWriteEnable = false;
		AlphaBlendEnable = false;
		VertexShader = NULL;//compile vs_3_0 MeshVS();
		PixelShader = compile ps_3_0 BrightnessPS();
	}
};


