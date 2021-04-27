matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;


matrix TempViewMatrix;
matrix TempProjMatrix;



float AmbientFactor;

texture CubeTex;
sampler CubeSampler = sampler_state
{
	Texture = (CubeTex);
};
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
    AddressU = clamp;
    AddressV = clamp;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
};
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
};

void AmbientLightVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}

float4 AmbientLightPS(
	float2 texcoord : TEXCOORD0
	) : COLOR0
{
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);

	return albedoMap * AmbientFactor;
}



technique AmbientLight
{
	pass P0
	{
		ZEnable = false;
		VertexShader = compile vs_3_0 AmbientLightVS();
		PixelShader = compile ps_3_0 AmbientLightPS();
	}
}