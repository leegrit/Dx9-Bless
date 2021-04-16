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


void SkyboxVS(
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

void SkyboxPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	

	outColor = albedo;
	/* Test */
	outColor = float4(1, 0, 0, 1);
}


technique Skybox
{
	pass P0
	{
		ZWRITEENABLE = false;
		CULLMODE = CW;
		VertexShader = compile vs_3_0 SkyboxVS();
		PixelShader = compile ps_3_0 SkyboxPS();
	}
};
