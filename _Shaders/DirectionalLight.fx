matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;

/* For Specular */
float3 EyePosition;

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
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
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
	out float2 outTexcoord : TEXCOORD0,
	out float3 outViewDirection : TEXCOORD1,
	out float3 outReflection : TEXCOORD2
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
	float4 specularMap = tex2D(SpecularSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);


	float3 normal = normalMap * 2 - 1;
	normal = normalize(normal);
	float3 lightDir = normalize(-Direction);
	float3 finalColor;
	finalColor = float3(0, 0, 0);
	float lightIntensity = saturate(dot(lightDir, normal.rgb));

	/* depthMap.rgb is emissive */
	float3 emissive = depthMap.rgb;
	finalColor += lightIntensity * albedoMap.rgb * Diffuse.rgb + emissive;

	/* Calculate world position */
	float4 worldPos;
	worldPos.x = texcoord.x * 2.f - 1.f;
	worldPos.y = texcoord.y * -2.f + 1.f;
	worldPos.z = depthMap.a;
	worldPos.w = 1;

	worldPos = mul(worldPos, ProjMatrixInv);
	worldPos = mul(worldPos, ViewMatrixInv);

	worldPos = worldPos / worldPos.w;

	/* Calculate Specular */
	float3 specular = float3(0, 0, 0); 
	if(finalColor.x > 0)
	{
		float3 viewDirection = normalize(EyePosition.xyz - worldPos.xyz);
		float3 reflection = 2 * lightIntensity * normal - lightDir;  //reflect(lightDir, normal);
		reflection = normalize(reflection);
		float specularIntensity = saturate(dot(reflection, viewDirection));

		specular = pow(specularIntensity, SpecularPower);
		specular = specular * specularMap.rgb;
	}
	finalColor = saturate(finalColor + specular.rgb);

	// depth rgb is emissive color
	return float4(finalColor.rgb + stashMap.rgb, 1) ;//+ float4(depthMap.rgb, 1);

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
