matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};
texture AlphaMaskTex;
sampler AlphaMaskSampler = sampler_state
{
	Texture = (AlphaMaskTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};


void MeshEffectVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}

void MeshEffectPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 alphaMask = tex2D(AlphaMaskSampler, texcoord);

	outColor = albedo * alphaMask;
	// test
	outColor = albedo;
}


technique MeshEffect
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = CCW;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 MeshEffectVS();
		PixelShader = compile ps_3_0 MeshEffectPS();
	}
};
