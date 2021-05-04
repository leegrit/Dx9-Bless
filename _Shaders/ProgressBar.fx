matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float Amount;

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

texture FillTex;
sampler FillSampler = sampler_state
{
	Texture = (FillTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = None;
	AddressU = wrap;
	AddressV = wrap;
};

texture BackTex;
sampler BackSampler = sampler_state
{
	Texture = (BackTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = None;
	AddressU = wrap;
	AddressV = wrap;
};

void ProgressVS(
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

void ProgressPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);

	if(texcoord.x > Amount)
		discard;

	outColor = albedo;
}

void BillboardBarPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
)
{
	float4 fill = tex2D(FillSampler, texcoord);
	float4 back = tex2D(BackSampler, texcoord);

	if (texcoord.x > Amount)
		outColor = back;
	else
		outColor = fill;

}

technique ProgressBar
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 ProgressVS();
		PixelShader = compile ps_3_0 ProgressPS();
	}
};

technique BillboardBar
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 ProgressVS();
		PixelShader = compile ps_3_0 BillboardBarPS();
	}
};
