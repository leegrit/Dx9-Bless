matrix WorldMatrix;
matrix ProjMatrix;

float Alpha;



void FadeInOutVS(
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

void FadeInOutPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	outColor = float4(0, 0, 0, Alpha);
}


technique FadeInOut
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 FadeInOutVS();
		PixelShader = compile ps_3_0 FadeInOutPS();
	}
};
