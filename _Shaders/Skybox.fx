matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

texture SkyboxTex;
samplerCUBE SkyboxSampler = sampler_state
{
	texture = SkyboxTex;
};

void SkyboxVS(
	float4 position : POSITION,
	float3 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float3 outTexcoord : TEXCOORD0
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}

void SkyboxPS(
	float3 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	float4 albedo = texCUBE(SkyboxSampler, texcoord);
	

	outColor = albedo;
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
