matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

void SimpleVS
(
	float4 position : POSITION,
	out float4 outPosition : POSITION
)
{
	  /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);
}
float4 SimplePS() : COLOR
{
	return float4(1, 1, 1, 1);
}

technique OcclusionQuery
{
	pass P0
	{
		VertexShader = compile vs_3_0 SimpleVS();
		PixelShader = compile ps_3_0 SimplePS();


	}
};
