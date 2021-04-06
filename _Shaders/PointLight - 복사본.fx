matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;


matrix TempViewMatrix;
matrix TempProjMatrix;

float4 Diffuse;

float3 LightPosition;
float LightAmbient;
float LightRange;
float3 LightDiffuse;


float LightConstant;
float LightLinear;
float LightExp;

texture CubeTex;
sampler CubeSampler = sampler_state
{
	Texture = (CubeTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};

float4 CalcPointLight(float3 albedo, float3 worldPos, float3 normal)
{
	float3 lightDirection = worldPos - LightPosition;
	float distance = length(lightDirection);

	lightDirection = normalize(lightDirection);

	//float4 ambientColor = float4(Diffuse.xyz, 1.0);
	float diffuseFactor = dot(normal, -lightDirection);
	float4 diffuseColor = 0;

	if(diffuseFactor > 0.0)
	{
		diffuseColor = float4(albedo * diffuseFactor, 1.0f);
	}
	diffuseColor = diffuseColor * diffuseFactor;

	float attention = pow((LightRange - distance) / LightRange, 2);
	diffuseColor = diffuseColor * attention;
	diffuseColor.w = 1;
return diffuseColor;
}


void PointLightVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0,
	out float4 outClipPos : TEXCOORD1
)
{
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
	outClipPos = outPosition;
}

float4 PointLightPS(
	float2 texcoord : TEXCOORD0,
	float4 clipPos : TEXCOORD1
	) : COLOR0
{
	float2 screenUV = clipPos.xy / clipPos.w;
	screenUV = 0.5f * screenUV + 0.5f;
	screenUV.y = 1 - screenUV.y;
	float2 uvRT = screenUV + float2(0.5f / 800, 0.5f / 600);
	//texcoord = uvRT;

	//float4 baseColor = tex2D(CubeSampler, texcoord);
	float4 depthMap  = tex2D(DepthSampler, texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);
	float4 specularMap = tex2D(SpecularSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);
	 
	float4 diffuse = albedoMap;
	normalMap = normalMap * 2.f - 1.f;

	float3 finalColor = float3(0.0f, 0.0f, 0.0f);

	// near ~ far
	float linearZ = depthMap.y * 1000;

	float4 tempPos;
	tempPos.x = (texcoord.x * 2.f - 1.f) * linearZ;
	tempPos.y = (texcoord.y * -2.f + 1.f) * linearZ;
	tempPos.z = depthMap.x * linearZ;
	tempPos.w = linearZ;

	tempPos = mul(tempPos, ProjMatrixInv);
	tempPos = mul(tempPos, ViewMatrixInv);

	
	float4 clipSpacePosition = float4(texcoord.x * 2.0f - 1.0f, 
			(1-texcoord.y) * 2.0f - 1.0f, depthMap.x, 1);
	
	
	float4 projSpacePosition = mul(clipSpacePosition, ProjMatrixInv);
	float4 worldSpacePosition = mul(projSpacePosition, ViewMatrixInv);
	worldSpacePosition = worldSpacePosition / worldSpacePosition.w;
	
	worldSpacePosition=  tempPos;
	


	float3 dir = LightPosition - worldSpacePosition.xyz;

	float dist = length(dir);

	float attenuation = max(0, 1 - dist / LightRange);

	dir /= dist;

	float NDL = saturate(dot(normalMap.xyz, dir));



	float3 lightToPixelVec = LightPosition - (float3)worldSpacePosition;
	float3 diffuse2 = NDL * LightDiffuse.xyz * albedoMap.xyz * attenuation;

	
	return float4(diffuse2 + stashMap.rgb, 1);
}



technique PointLight
{
	pass P0
	{
		VertexShader = compile vs_3_0 PointLightVS();
		PixelShader = compile ps_3_0 PointLightPS();
	}
}