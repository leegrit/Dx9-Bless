matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;


/* 나중에 따로 분리 */
/* For Light Data */
float3 Direction;
float3 Position;
float4 Ambient;
float  AmbientIntensity;
float4 Diffuse;
float  DiffuseIntensity;
float4 Specular;
float  SpecularIntensity;
float  SpecularPower;
float  Constant;
float  Linear;
float  Quadratic;





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
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
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
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};


void DirectionalLightVS(
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

float4 DirectionalLightPS(
	float2 texcoord : TEXCOORD0
	) : COLOR0
{
	float4 depthMap = tex2D(DepthSampler, texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);


	float3 normal = normalMap * 2 - 1;
	normal = normalize(normal);
	float3 lightDir = normalize(-Direction);
	float3 finalColor;
	finalColor = float3(0, 0, 0);
	float lightIntensity = saturate(dot(lightDir, normal.rgb));
	finalColor += lightIntensity * albedoMap.rgb * Diffuse.rgb;
	//finalColor += saturate(float4((saturate(dot(lightDir.xyz, normalMap.xyz)), 1) * albedoMap * Diffuse));

	return float4(finalColor.rgb + stashMap.rgb, 1);

}


technique DirectionalLight
{
	pass P0
	{
		ZEnable = false;
		VertexShader = compile vs_3_0 DirectionalLightVS();
		PixelShader = compile ps_3_0 DirectionalLightPS();
	}
};
