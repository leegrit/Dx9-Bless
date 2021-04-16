matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float3 ColliderColor;


void ColliderVS(
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

void ColliderPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	outColor = float4(ColliderColor, 1);
}


technique Collider
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = CCW;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		FILLMODE = WIREFRAME;
		VertexShader = compile vs_3_0 ColliderVS();
		PixelShader = compile ps_3_0 ColliderPS();
	}
};
