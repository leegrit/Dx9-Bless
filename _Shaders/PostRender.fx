

texture RimLightTex;
sampler RimLightSampler = sampler_state
{
	texture =(RimLightTex);
};


texture BloomTex;
sampler BloomSampler = sampler_state
{
	Texture = (BloomTex);
};

struct PixelOutput
{
	float4 color : COLOR0; // backbuffer
};

PixelOutput PostRenderPS(float2 texcoord : TEXCOORD0)
{
	PixelOutput output = (PixelOutput)0;

	float4 rimLightMap =tex2D(RimLightSampler, texcoord);
	float4 bloomMap = tex2D(BloomSampler, texcoord);
	
	output.color = rimLightMap + bloomMap;
	
	return output;
};


technique PostRender
{
	pass P0
	{
		ZWriteEnable = false;
		AlphaBlendEnable = true;
		BlendOp = ADD;
		SrcBlend = ONE;
		DestBlend = ONE;
		VertexShader = NULL;//compile vs_3_0 MeshVS();
		PixelShader = compile ps_3_0 PostRenderPS();
	}
};


