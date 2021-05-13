matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;






void DiffuseVS(
	float4 position : POSITION,
	float4 color : COLOR0,
	out float4 outPosition : POSITION,
	out float4 outColor : TEXCOORD0
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outColor = color;
}

void DiffusePS(
	float4 color : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{

	outColor = color;
}


technique DiffuseShader
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = NONE;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = NULL;//compile vs_3_0 DiffuseVS();
		PixelShader = compile ps_3_0 DiffusePS();
	}
};
