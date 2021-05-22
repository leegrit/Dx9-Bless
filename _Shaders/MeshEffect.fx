matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Border;
	AddressV = Border;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
	AddressU = Border;
	AddressV = Border;
};
texture AlphaMaskTex;
sampler AlphaMaskSampler = sampler_state
{
	Texture = (AlphaMaskTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Border;
	AddressV = Border;
};

float Alpha;
float2 UVMoveFactor;

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
	float2 texcoord2 = texcoord;
	texcoord2 += UVMoveFactor;
	float4 albedo = tex2D(AlbedoSampler, texcoord2);
	float4 alphaMask = tex2D(AlphaMaskSampler, texcoord2);

	//outColor = albedo * alphaMask;
	// test
	outColor = albedo * Alpha;
}
void MeshEffectWithAlphaMaskPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
)
{
	float2 texcoord2 = texcoord;
	texcoord2 += UVMoveFactor;
	float4 albedo = tex2D(AlbedoSampler, texcoord2);
	float4 alphaMask = tex2D(AlphaMaskSampler, texcoord2);
	//float alphaMaskAlpha = saturate( alphaMask.r + alphaMask.g + alphaMask.b);
	outColor = albedo * alphaMask.r * Alpha;
	// test
	//outColor = albedo * Alpha;
}

technique MeshEffect
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = NONE;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 MeshEffectVS();
		PixelShader = compile ps_3_0 MeshEffectPS();
	}
};
technique MeshEffectWithAlphaMask
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = NONE;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 MeshEffectVS();
		PixelShader = compile ps_3_0 MeshEffectWithAlphaMaskPS();
	}
};
