matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

matrix ViewMatrixInv;
matrix ProjMatrixInv;

float3 LightDir;
float3 CameraEye;

float DiffuseIntensity;
float SpecularIntensity;
// 반사광 제곱수
float SpecularPower;
float4 Diffuse;
float4 Specular;



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

void DirectionalLightVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float3 outLight : TEXCOORD0,
	out float2 outTexcoord : TEXCOORD1
)
{
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);
	float3 lightDirNorm = normalize(LightDir);
	outLight = -lightDirNorm;
	outTexcoord = texcoord;
}

float4 DirectionalLightPS(
	float3 light : TEXCOORD0,
	float2 texcoord : TEXCOORD1
	) : COLOR0
{
	float4 depthMap = tex2D(DepthSampler, texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);
normalMap = normalize(normalMap);
	float4 clipSpacePosition = float4(texcoord.x * 2.0f - 1.0f, 
									texcoord.y * 2.0f - 1.0f, 
									depthMap.x, 1);
	float4 projSpacePosition = mul(clipSpacePosition, ProjMatrixInv);
	float4 worldSpacePosition = mul(projSpacePosition, ViewMatrixInv);

/*
	// 카메라가 해당 오브젝트 바라보는 정규화된 방향벡터
	float3 View = (float3)worldSpacePosition - CameraEye;
	View = normalize(View);

	// Compute the reflection vector
	float3 reflect = normalize(2 * dot((float3)normalMap, light) * (float3)normalMap - light);


	// Compute diffuse 
	float4 diffuseColor = Diffuse * DiffuseIntensity * max(0, dot((float3)normalMap, light));

	// Compute specular
	float4 specularColor = Specular * SpecularIntensity * pow(max(0, dot(reflect, View)), SpecularPower);

	float4 finalColor = diffuseColor * albedoMap + specularColor;
*/
	float finalColor = float4(0, 0, 0, 0);

	float diffuseStrength = max(dot(light, (float3)normalMap), 0.0f);
	//return float4(-light, 1);
	//return float4(abs(normalMap.z), 0, 0, 1);
	//return float4(diffuseStrength, 0, 0, 1);
	float4 diffuse = Diffuse *diffuseStrength * albedoMap;
	finalColor = diffuse;

	return finalColor + stashMap;
}



technique DirectionalLight
{
	pass P0
	{
		VertexShader = compile vs_3_0 DirectionalLightVS();
		PixelShader = compile ps_3_0 DirectionalLightPS();
	}
}