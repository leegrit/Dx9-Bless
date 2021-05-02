matrix WorldMatrix;
matrix ProjMatrix;

float Alpha;

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


void UIPanelVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}

void UIPanelPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);

	outColor = albedo * Alpha;
}


technique UIPanel
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 UIPanelVS();
		PixelShader = compile ps_3_0 UIPanelPS();
	}
};
