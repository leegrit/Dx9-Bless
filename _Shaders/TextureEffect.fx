matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float Alpha;
float2 UVMoveFactor;

texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
	AddressU = Border;
	AddressV = Border;
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
	AddressU = Border;
	AddressV = Border;
};


void TextureEffectVS(
	float4 position : POSITION,
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

void TextureEffectPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	texcoord += UVMoveFactor;
	float4 albedo = tex2D(AlbedoSampler, texcoord);

	outColor = albedo * Alpha;
}
void TextureEffectWithAlphaMaskPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
)
{
	texcoord += UVMoveFactor;
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 alphaMask = tex2D(AlphaMaskSampler, texcoord);

	outColor = albedo * alphaMask.r * Alpha;
}

technique TexturehEffect
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = NONE;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 TextureEffectVS();
		PixelShader = compile ps_3_0 TextureEffectPS();
	}
};
technique TexturehEffectWithAlphaMask
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = NONE;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 TextureEffectVS();
		PixelShader = compile ps_3_0 TextureEffectWithAlphaMaskPS();
	}
};
