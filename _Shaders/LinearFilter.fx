matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

void LinearFilterVS
(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
	outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}


float4 LinearFilterPS(
	float2 texcoord : TEXCOORD0
	) : COLOR0
{
	float4 stashMap = tex2D(StashSampler, texcoord);

	return stashMap;
}



technique LinearFilter
{
	pass P0
	{
		ZEnable = false;
		ZWriteEnable = false;
		VertexShader = compile vs_3_0 LinearFilterVS();
		PixelShader = compile ps_3_0 LinearFilterPS();
	}
}